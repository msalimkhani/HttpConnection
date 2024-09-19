#pragma once
#define FMT_HEADER_ONLY
#include <iostream>
#include <fmt/core.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <charconv>
using namespace std;
class Logger
{
private:
    /* data */
public:
    Logger(/* args */);
    ~Logger();
    void Log(const string &msg);
    void LogError(const string &msg);
};



template <typename T>
bool parse(const std::string& str, T& result)
{
    result = T();
    
    // https://en.cppreference.com/w/cpp/utility/from_chars
    auto [p, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
    return (ec == std::errc()); // true if no errors
}
template <char C>
std::istream& expect(std::istream& in)
{
    if ((in >> std::ws).peek() == C) {
        in.ignore();
    }
    else {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}