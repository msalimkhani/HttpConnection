#include "Logger.h"

Logger::Logger(){
    this->Log("Logger: Constructor Called!");
}

Logger::~Logger(){
    this->Log("Logger: Destructor Called");
}

void Logger::Log(const string &msg){
    fmt::print("HttpConnection: {0}\n", msg);
}
void Logger::LogError(const string &msg)
{
    fmt::system_error(1, "HttpConnection: {0}\n", msg);
}