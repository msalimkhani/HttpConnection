#pragma once
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

std::vector<string> split(char *source, const char *delim, int count = 0)
{
    std::vector<string> res;
    auto token = strtok(source, delim);
    int i = 0;
    while ((count == 0)?(token != NULL) : (token != NULL && i < count))
    {
        res.push_back(token);
        token = strtok(NULL, delim);
        i++;
    }
    return res;
}