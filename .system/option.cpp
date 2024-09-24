#include "option.h"
#include <filesystem>
#include <cstdlib>

#include "utils.h"

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
    std::string home_directory = get_user_home_directory();
    std::filesystem::path exam_dir = home_directory + "/42-EXAM/";
    if (std::filesystem::exists(exam_dir))
        std::filesystem::remove_all(exam_dir);
    std::filesystem::create_directories(exam_dir);
}