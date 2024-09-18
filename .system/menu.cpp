#include "menu.h"
#include "exam_simulator.h"
#include "exercice_grading.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <string>

Menu::Menu()
{
    options.push_back(new ExamSimulator());
    options.push_back(new ExerciceGrading());
}

void Menu::display()
{
    char input;
    int option_index;
    system("clear");
    write_colored_text(R"(
   __ __ ___      _______  __ ___    __  ___   __________  ___    _____   ____________ 
  / // /|__ \    / ____/ |/ //   |  /  |/  /  /_  __/ __ \/   |  /  _/ | / / ____/ __ \
 / // /___/ /   / __/  |   // /| | / /|_/ /    / / / /_/ / /| |  / //  |/ / __/ / /_/ /
/__  __/ __/   / /___ /   |/ ___ |/ /  / /    / / / _, _/ ___ |_/ // /|  / /___/ _, _/ 
  /_/ /____/  /_____//_/|_/_/  |_/_/  /_/    /_/ /_/ |_/_/  |_/___/_/ |_/_____/_/ |_|   
    )", "\x1b[31m", true);
    std::cout << "Made by ";
    write_colored_text("Noe-prt", "\x1b[38;5;11m", true);
    std::cout << "Visit: ";
    write_colored_text("https://github.com/Noe-prt ", "\x1b[38;5;11m", false);
    std::cout << "to see the code source of this project" << std::endl;
    std::cout << "" << std::endl;
    for (size_t i = 0; i < options.size(); ++i)
    {
        std::cout << "[";
        write_colored_text(std::to_string(i + 1), "\x1b[31m", false);
        std::cout << "]";
        std::cout << options[i]->name << std::endl;
    }
    std::cout << "Please, Choose an option to continue..." << std::endl;
    input = advanced_getch();
    option_index = input -= '0';
    while (!(option_index > 0 && option_index <= options.size()))
    {
        write_colored_text("Invalid option! Please try again", "\x1b[31m", true);
        input = advanced_getch();
        option_index = input - '0';
    }
    options[option_index - 1]->on_select_function();
}

Menu::~Menu()
{
    for (auto option : options)
    {
        delete option;
    }
    options.clear();
}
