#pragma once
#include <iostream>

using namespace std;

class HttpResponse
{
private:
    string result;
public:
    HttpResponse(/* args */)
    {

    }
    void setResult(string val)
    {
        this->result = val;
    }
    string getResult()
    {
        return this->result;
    }
    ~HttpResponse()
    {
        
    }
};
