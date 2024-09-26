#include "exercice_grading.h"
#include "utils.h"
#include "exercice_data.h"
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>

#endif

ExerciceGrading::ExerciceGrading()
{
    name = "ExerciceGrading";
    exercices_list = ExerciceData::get_exercices(".data/exercices.json");
}

  // Pour std::numeric_limits

void ExerciceGrading::on_select_function()
{
    Option::on_select_function();
    display_exercices();
    display_grading_page(get_selected_exercice());

}

ExerciceData ExerciceGrading::get_selected_exercice()
{
    std::string input;
    int exercice_index;
    std::vector<ExerciceData> exercices = ExerciceData::get_exercices(".data/exercices.json");
    while (true) 
    {
        std::getline(std::cin, input);
        exercice_index = ft_atoi(input);
        if (exercice_index > 0 && exercice_index <= exercices.size())
        {
            ExerciceData ex = ExerciceData::get_exercice_by_index(exercice_index);
            return ex;
        }
        else
            write_colored_text("ERROR: Not a valid exercice index!", "\e[91m", true);
    }
}



void ExerciceGrading::display_exercices()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    std::vector<ExerciceData> exercices = ExerciceData::get_exercices(".data/exercices.json");
    ExerciceData last_exercice = exercices.back();
    int ex_index = 1;
    for (int i = 0; i <= last_exercice.level; i++)
    {
        std::cout << "Level ";
        write_colored_text(std::to_string(i), "\x1b[31m", false);
        std::cout << ":" << std::endl;
        std::vector<ExerciceData> exercices_by_level = ExerciceData::get_exercises_by_level(exercices, i);
        for (const auto& ex : exercices_by_level)
        {
            write_colored_text("    - ", "\x1b[31m", false);
            std::cout << "[";
            write_colored_text(std::to_string(ex_index), "\x1b[31m", false);
            std::cout << "] ";
            std::cout << ex.name << std::endl;
            ex_index++;
        }
    }
}

void ExerciceGrading::display_grading_page(ExerciceData exercice)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    std::string home_directory = get_user_home_directory();
    std::filesystem::path exercice_dir = home_directory + "/42-EXAM/rendu/" + exercice.name;
    if (!std::filesystem::exists(exercice_dir))
        std::filesystem::create_directories(exercice_dir);
    std::string option;
    std::cout << "=================================================================================" << std::endl;
    std::cout << "You selected ";
    write_colored_text(exercice.name, "\x1b[31m", true);
    std::cout << "Exercice Location:";
    write_colored_text(" ~/42-EXAM/rendu/" + exercice.name, "\x1b[31m", true);
    std::cout << "Exercice Level: ";
    write_colored_text(std::to_string(exercice.level), "\x1b[31m", true);
    std::cout << "================================== SUBJECT ======================================" << std::endl;
    display_subject(".subjects/" + exercice.name + ".txt");
    std::cout << "" << std::endl;
    std::cout << "=================================================================================" << std::endl;
    std::cout << "Use the \"";
    write_colored_text("grademe", "\x1b[38;5;46m", false);
    std::cout << "\" command to be graded, or \"";
    write_colored_text("help", "\x1b[38;5;46m", false);
    std::cout << "\" to get some help." << std::endl;
    while (1)
    {
        write_colored_text("examshell", "\x1b[38;5;11m", false);
        std::cout << "> ";
        std::getline(std::cin, option);
        if (option == "grademe")
        {
            std::string input;
            std::cout << "" << std::endl;
            std::cout << "Before continuing, please make ";
            write_colored_text("ABSOLUTELY SURE", "\e[91m", false);
            std::cout << " that you are in the right directory," << std::endl;
            std::cout << "that you didn't forget anything, etc..." << std::endl;
            std::cout << "If your assignment is wrong, you will have the same assignment" << std::endl;
            std::cout << "" << std::endl;
            std::cout << " but with less potential points to earn !" << std::endl;
            write_colored_text("Are you sure?", "\e[91m", false);
            std::cout << " [y/N] ";
            std::getline(std::cin, input);
            if (input == "y" || input == "Y")
            {
                std::cout << "Please be ";
                write_colored_text("patient", "\x1b[38;5;46m", false);
                std::cout << ", this ";
                write_colored_text("CAN ", "\x1b[38;5;46m", false);
                std::cout << "take several minutes..." << std::endl;
                std::cout << "(10 seconds is fast, 30 seconds is expected, 3 minutes is a maximum)" << std::endl;
                multi_sleep(2000);
                std::cout << "waiting..." << std::endl;
                multi_sleep(2000);
                std::cout << "waiting..." << std::endl;
                multi_sleep(2000);
                std::cout << "waiting..." << std::endl;
                multi_sleep(2000);
                std::cout << "" << std::endl;
                if (grade_me(exercice.name))
                {      
                    write_colored_text("<<<<<<<<<< SUCCESS >>>>>>>>>>", "\x1b[38;5;10m", true);
                    multi_sleep(2000);
                }
                else
                {
                    write_colored_text("<<<<<<<<<< FAILURE >>>>>>>>>>", "\x1b[31m", true);
                    multi_sleep(700);
                    std::cout << "You have failed the assignment." << std::endl;
                    std::cout << "" << std::endl;
                    std::cout << "(Press enter to continue...)" << std::endl;
                    std::string input;
                    std::getline(std::cin, input);
                }
            }
            else
                std::cout << " Abort" << std::endl;

        }
        else if (option == "exit")
        {
            std::string str;
            std::cout << "Are you sure you want to ";
            write_colored_text("exit", "\e[91m", false);
            std::cout << " the exam?" << std::endl;
            std::cout << "All your progress will be ";
            write_colored_text("lost", "\e[91m", false);
            std::cout << "." << std::endl;
            std::cout << "Type ";
            write_colored_text("yes", "\e[92m", false);
            std::cout << " to confirm." << std::endl;
            std::getline(std::cin, str);
            if (str == "yes")
                break;
            else
                std::cout << " ** Abort **" << std::endl;
                multi_sleep(1000);
        }
        else
        {
            std::cout << "         **Unknown command**     type ";
            write_colored_text("help", "\x1b[38;5;46m", false);
            std::cout << " for more help" << std::endl;
        }
    }
}

void ExerciceGrading::display_subject(const std::string& file_path)
{
    std::ifstream file(file_path);
    std::string line;
    while (std::getline(file, line))
        std::cout << line << std::endl;
    file.close();
}
