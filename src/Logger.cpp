#include "Logger.h"

Logger::Logger(){
    this->Log("Logger: Initialized");
}

Logger::~Logger(){
}

void Logger::Log(const string &msg){
    fmt::print("\033[0;32mHttpConnection:\033[0m {0}\n", msg);
}
void Logger::LogError(const string &msg)
{
    fmt::system_error(1, "\033[0;32mHttpConnection:\033[0m \033[0;31m{0}\033[0m\n", msg);
}