#pragma once
#include <iostream>
#include <fmt/core.h>

#include <vector>

using namespace std;

class HttpRequest
{
private:
    string method;
    string path;

    vector<std::pair<string, string>> requestDictionary;
public:

    string getMethod(){
        return method;
    }

    void setMethod(string val)
    {
        this->method = val;
    }
    string getPath(){
        return path;
    }

    void setPath(string val)
    {
        this->path = val;
    }

    void addToRequestDictionary(pair<string, string> item)
    {
        this->requestDictionary.push_back(item);
    }
    
    vector<pair<string, string>> gettAllRequest(){
        return requestDictionary;
    }


    string toString(){
        auto resPart = fmt::format("<p>Method: {0}, Path: {1}</p>", method, path);
        string keyValues;
        for(auto item : requestDictionary)
        {
            keyValues.append(fmt::format("<li>Key: {0}, Value: {1}</li>", item.first, item.second));
        }
        string final_res = fmt::format("{0}<div><ul>{1}</div></ul>", resPart, keyValues);
        return final_res;
    }

    void print(){
        printf("Method: %s, Path: %s\r\n", this->method.c_str(), this->path.c_str());
        for(auto item : requestDictionary)
        {
            printf("Key: %s, Value: %s\r\n", item.first.c_str(), item.second.c_str());
        }
    }

    void clear(){
        requestDictionary.clear();
    }
};