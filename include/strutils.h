#pragma once
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

std::vector<string> split(char *source, const char *delim)
{
    std::vector<string> res;
    auto token = strtok(source, delim);
    while (token != NULL)
    {
        res.push_back(token);
        token = strtok(NULL, delim);
    }
    return res;
}