#pragma once

#include <vector>
#include "option.h"

class Menu
{
public:
    Menu();
    ~Menu();
    void display();

private:
    std::vector<Option*> options;
};