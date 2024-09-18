#include "option.h"
#include <cstdlib>

Option::Option()
{

}


Option::~Option()
{

}

void Option::on_select_function()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}