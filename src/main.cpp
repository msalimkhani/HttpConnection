#include "HttpConnection.h"

int main(int argc, char const *argv[])
{
    HttpConnection *conn;
    conn = new HttpConnection("127.0.0.1", 8080);
    conn->mapPath("/home", [](HttpRequest req, HttpResponse* res){
        string resHtml = "<!DOCTYPE html><html lang=\"en\"><body><h1> Home </h1></body></html>";
        res->setResult(resHtml);
    });
    conn->mapPath("/about", [](HttpRequest req, HttpResponse* res){
        string resHtml = "<!DOCTYPE html><html lang=\"en\"><body><h1> About </h1></body></html>";
        res->setResult(resHtml);
    });
    conn->run();
    return 0;
}
