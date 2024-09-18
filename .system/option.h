#pragma once

#include <string.h>
#include <iostream>

using namespace std;

class Option
{
public:
    Option();
    virtual ~Option();
    virtual void on_select_function();
    string name;
};

