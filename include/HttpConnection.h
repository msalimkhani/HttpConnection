#pragma once
#include <iostream>
#include "Logger.h"
#include "HttpRequest.hpp"
#include <vector>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <list>

using namespace std;

class HttpConnection
{
private:
    int m_server_fd;
    string m_ip_addr;
    int m_port;
    int m_client_fd;
    long m_incomingMessage;
    struct sockaddr_in m_serverAddress;
    unsigned int m_serverAddress_len;
    string m_server_message;
    Logger _logger;
    void strartServer();
    void closeServer();
    void startListen();
    void processConnection();
    void acceptConnection(int &new_socket);
    void sendResponse(const string& response);
    /* data */
public:
    HttpConnection(string ip_addr, int port);
    void run();
    ~HttpConnection();
};