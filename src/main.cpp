#include "HttpConnection.h"

int main(int argc, char const *argv[])
{
    HttpConnection *conn;
    conn = new HttpConnection("127.0.0.1", 8080);
    conn->run();
    return 0;
}
