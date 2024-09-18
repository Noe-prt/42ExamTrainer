#include "exercice_grading.h"
#include "utils.h"
#include "exercice_data.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>

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

#include <iostream>
#include <limits>  // Pour std::numeric_limits

void ExerciceGrading::on_select_function()
{
    Option::on_select_function();
    display_exercices();
    display_grading_page(get_selected_exercice());
}

ExerciceData ExerciceGrading::get_selected_exercice()
{
    string input;
    int exercice_index;
    std::cout << "Please, Choose an exercice index to continue..." << std::endl;
    cin >> input;
    std::vector<ExerciceData> exercices = ExerciceData::get_exercices(".data/exercices.json");
    try
    {
        exercice_index = std::stoi(input);
        ExerciceData exercice = ExerciceData::get_exercice_by_index(exercice_index);
        return exercice;
    }
    catch (const std::invalid_argument& e)
    {
        write_colored_text("Invalid option! Please try again", "\x1b[31m", true);
        return ExerciceGrading::get_selected_exercice();
    }
    catch (const std::out_of_range& e)
    {
        write_colored_text("Invalid option! Please try again", "\x1b[31m", true);
        return ExerciceGrading::get_selected_exercice();
    }
    catch (std::runtime_error& e)
    {
        write_colored_text("Invalid option! Please try again", "\x1b[31m", true);
        return ExerciceGrading::get_selected_exercice();
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
    std::filesystem::path exercice_dir = home_directory + "/42-Exam/rendu/" + exercice.name;
    if (!std::filesystem::exists(exercice_dir))
        std::filesystem::create_directories(exercice_dir);
    std::string option;
    std::cout << "=================================================================================" << std::endl;
    std::cout << "You selected ";
    write_colored_text(exercice.name, "\x1b[31m", false);
    std::cout << ", to be graded, type: ";
    write_colored_text("grademe", "\x1b[31m", true);
    std::cout << "Exercice Location:";
    write_colored_text(" ~/42-Exam/rendu/" + exercice.name, "\x1b[31m", true);
    std::cout << "Exercice Level: ";
    write_colored_text(std::to_string(exercice.level), "\x1b[31m", true);
    std::cout << "================================== SUBJECT ======================================" << std::endl;
    display_subject(".subjects/" + exercice.name + ".txt");
    write_colored_text("grademe", "\x1b[38;5;11m", false);
    std::cout << ">";
    std::cin >> option;
    while (option != "grademe")
    {
        write_colored_text("grademe", "\x1b[38;5;11m", false);
        std::cout << ">";
        std::cin >> option;
    }
    if (grade_me(exercice.name))
    {
        std::cout << "Please be ";
        write_colored_text("patient", "\e[0; 32m", false);
        std::cout << ", this ";
        write_colored_text("CAN ", "\e[0; 32m", false);
        std::cout << "take several minutes..." << std::endl;
        std::cout << "(10 seconds is fast, 30 seconds is expected, 3 minutes is a maximum)" << std::endl;
        multi_sleep(2);
        std::cout << "waiting..." << std::endl;
        multi_sleep(2);
        std::cout << "waiting..." << std::endl;
        multi_sleep(2);
        std::cout << "waiting..." << std::endl;
        multi_sleep(2);
        write_colored_text("<<<<<<<<<< SUCCESS >>>>>>>>>>", "\x1b[38;5;10m", true);
        multi_sleep(2);
        return ExerciceGrading::on_select_function();
    }
    else
    {
        std::cout << "Please be ";
        write_colored_text("patient", "\e[0;32m", false);
        std::cout << ", this ";
        write_colored_text("CAN ", "\e[0;32m", false);
        std::cout << "take several minutes..." << std::endl;
        std::cout << "(10 seconds is fast, 30 seconds is expected, 3 minutes is a maximum)" << std::endl;
        multi_sleep(2);
        std::cout << "waiting..." << std::endl;
        multi_sleep(2);
        std::cout << "waiting..." << std::endl;
        multi_sleep(2);
        std::cout << "waiting..." << std::endl;
        multi_sleep(2);
        write_colored_text("<<<<<<<<<< FAILURE >>>>>>>>>>", "\x1b[31m", true);
        multi_sleep(2);
        return ExerciceGrading::display_grading_page(exercice);
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
