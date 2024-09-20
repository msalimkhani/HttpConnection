#include "HttpConnection.h"
#include "strutils.h"
#include <pthread.h>

HttpConnection::HttpConnection(string ip_addr, int port):
m_client_fd(), m_incomingMessage(), m_ip_addr(ip_addr),
m_port(port), m_server_fd(), m_server_message(), m_serverAddress(),
m_serverAddress_len(sizeof(m_serverAddress))
{
    _logger.Log("Instance Created.");
}

HttpConnection::~HttpConnection()
{
    _logger.Log("HttpConnection: Destructor Called.");
    closeServer();
}

void HttpConnection::strartServer()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        _logger.LogError("Error in Create Socket.");
    }
    this->m_server_fd = socket_fd;
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);
    m_serverAddress.sin_addr.s_addr = inet_addr(m_ip_addr.c_str());

    if(bind(m_server_fd, (sockaddr *)&m_serverAddress, m_serverAddress_len) < 0)
    {
        _logger.LogError("Cannot Bind Socket to Address");
    }

    startListen();
    _logger.Log("Server Create Successfully");
}

void HttpConnection::closeServer(){
    close(this->m_server_fd);
    close(this->m_client_fd);
    exit(0);
}

void HttpConnection::startListen(){
    if(listen(m_server_fd, 20) < 0)
    {
        _logger.LogError("Socket Listen Failed");
    }

    _logger.Log(fmt::format("Server Listening on http://{0}:{1} ***\n", 
    inet_ntoa(m_serverAddress.sin_addr)  ,
    ntohs(m_serverAddress.sin_port)));
    
    processConnection();
}

void HttpConnection::acceptConnection(int &new_socket){
    new_socket= accept(m_server_fd, (sockaddr *)&m_serverAddress, &m_serverAddress_len);

    if(new_socket < 0)
    {
        _logger.LogError(fmt::format("Server Failed to Accept incoming connection from ADDRESS: {0}; PORT: {1}.\n", inet_ntoa(m_serverAddress.sin_addr), ntohs(m_serverAddress.sin_port)));
    }
}

void HttpConnection::sendResponse(const string& response){
    long bytesSent;

        bytesSent = write(m_client_fd, response.c_str(), response.size());

        if (bytesSent != response.size())
        {
            _logger.Log("Error while sending response to the client.");
        }
}

void HttpConnection::run(){
    try
    {
        strartServer();
    }
    catch(const std::exception& e)
    {
        cerr << fmt::format("\033[0;32mHttpConnection:\033[0m \033[0;31m{0}\033[0m", e.what()) << endl;
        cerr << "server_fd: " << this->m_server_fd << endl;
        closeServer();
    }
    
}

void HttpConnection::processConnection(){
    while (true)
    {
        int bytesReceived;

        acceptConnection(m_client_fd);

        char buffer[BUFSIZ] = {0};
        bytesReceived = read(m_client_fd, buffer, BUFSIZ);
        if (bytesReceived < 0)
        {
           _logger.LogError("Failed to read bytes from client socket connection");
        }

        vector<string> lines;
        HttpRequest req;
        lines = split(buffer, "\n");

        auto request = lines.at(0);
        char *met, *pat;
        met = (char *)malloc(BUFSIZ * sizeof(char));
        pat = (char *)malloc(BUFSIZ * sizeof(char));
        sscanf(request.c_str(), "%s %s HTTP/1.1", met, pat);
        req.setMethod(met);
        req.setPath(pat);
        lines.erase(lines.begin());

        for(auto item : lines)
        {
            const char *cStr = item.c_str();
            char *buff = (char *)malloc(strlen(cStr) * sizeof(char));
            sprintf(buff, "%s", cStr);
            auto splitted = split(buff, ":", 2);
            if(splitted.size() > 1)
            {
                auto key = splitted[0];
                auto val = splitted[1];
                req.addToRequestDictionary({key, val});
            }
        }
        
        HttpResponse response;
        _logger.Log(fmt::format("\033[0;32m{0} {1}\033[0m\n", req.getMethod(), req.getPath()));

        std::string htmlFile = fmt::format("<!DOCTYPE html><html lang=\"en\"><body><h1> {0} </h1><p>{1}</p></body></html>", req.getPath() ,req.toString());
        
        response.setResult(htmlFile);
        try
        {
            auto callback = routes.at(req.getPath());

            callback(req, &response);
        }
        catch(const std::exception& e)
        {
            cerr << fmt::format("\033[0;32mHttpConnection:\033[0m \033[0;31m{0}\033[0m", e.what()) << endl;
            std::string htmlFile = fmt::format("<!DOCTYPE html><html lang=\"en\"><body><h1> {0} NotFound </h1></body></html>", req.getPath());
            string res =  "HTTP/1.1 404 Not Found\nContent-Type: text/html\nContent-Length: {0}\nServer: MahdiServer(Linux Ubuntu)\n\n{1}";
            string ss = fmt::format(res, htmlFile.size(), htmlFile);
            //response.setResult(ss);
            sendResponse(ss);
        }
        

        string res =  "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: {0}\nServer: MahdiServer(Linux Ubuntu)\n\n{1}";
        string ss = fmt::format(res, response.getResult().size(), response.getResult());
        sendResponse(ss);
        close(m_client_fd);
    }
}

HttpConnection* HttpConnection::mapPath(string path, std::function<void(HttpRequest, HttpResponse*)> callback)
{
    routes.insert({path, callback});
    return this;
}