#include "exam_simulator.h"
#include "utils.h"
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstdio>
#include <cstring>
#include <pwd.h>

//#include "exercice_data.h"

using namespace std;

ExamSimulator::ExamSimulator()
{
    name = "ExamSimulator";
    current_grade = 0;
    max_grade = 100;
    current_level = 0;
    assignment_index = 0;
    exercice_xp = 6;
}

void ExamSimulator::on_select_function()
{
    Option::on_select_function();
    std::string home_directory = get_user_home_directory();
    std::filesystem::path rendu_dir = std::filesystem::path(home_directory) / "42-EXAM" / "rendu";
    std::filesystem::path subjects_dir = std::filesystem::path(home_directory) / "42-EXAM" / "subjects";
    std::filesystem::create_directories(rendu_dir);
    std::filesystem::create_directories(subjects_dir);

    set_current_exercice();
    DisplayExamPage();
}


void ExamSimulator::DisplayExamPage()
{
    std::cout << "\033[1m";
    write_underlined_text("ExamShell", true);
    std::cout << "" << std::endl;
    const char* login = getlogin();
    std::string option;
    if (!login)
    {
        struct passwd* pw = getpwuid(geteuid());
        if (pw)
            login = pw->pw_name;
    }
    write_bold_text("login:", false);
    for (int i = 0; i < strlen(login); i++)
    {
        std::cout << login[i] << std::flush;
        multi_sleep(300);
    }
    std::cout << "" << std::endl;
    write_bold_text("password:", false);
    for (int i = 0; i < 6; i++)
    {
        std::cout << "*" << std::flush;
        multi_sleep(300);
    }
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "You're connected ";
    write_colored_text(login, "\x1b[38;5;10m", false);
    std::cout << "!" << std::endl;
    std::cout << "You can log out at any time. If this program tells you you earned points,\nthen they will be counted whatever happens." << std::endl;
    std::cout << "" << std::endl;
    write_bold_text("You are about to start the project ", false);
    std::cout << "\033[1m";
    write_colored_text("ExamFinal", "\x1b[38;5;46m", false);
    write_bold_text(", in ", false);
    std::cout << "\033[1m";
    write_colored_text("REAL", "\x1b[38;5;13m", false);
    write_bold_text(" mode, at level ", false);
    std::cout << "\033[1m";
    write_colored_text("0", "\x1b[38;5;11m", false);
    write_bold_text(".", true);
    std::cout << "\033[1m";
    std::cout << "You would have ";
    write_colored_text("8hrs", "\x1b[38;5;46m", false);
    std::cout << "\033[1m";
    std::cout << " to complete this project." << std::endl;  
    std::cout << "\033[0m"; 
    std::cout << "Press a key to start exam 🏁" << std::endl;
    getchar();
    display_grading_box();
    while (1)
    {
        char *line = readline("\e[93mexamshell\e[0m> ");
        std::string option = line;
        free(line);
        while (option.back() == ' ')
            option.pop_back();
        while (option.front() == ' ')
            option.erase(option.begin());
        if (option.empty())
            continue;
        add_history(option.c_str());
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
                if (grade_me(current_exercice.name))
                {      
                    write_colored_text("<<<<<<<<<< SUCCESS >>>>>>>>>>", "\x1b[38;5;10m", true);
                    multi_sleep(2000);
                    assignment_data new_assignement{current_exercice, true};
                    assignments_history.push_back(new_assignement);
                    set_current_exercice();
                    display_grading_box();
                }
                else
                {
                    write_colored_text("<<<<<<<<<< FAILURE >>>>>>>>>>", "\e[91m", true);
                    multi_sleep(700);
                    std::cout << "You have failed the assignment." << std::endl;
                    std::cout << "" << std::endl;
                    std::cout << "(Press enter to continue...)" << std::endl;
                    std::string input;
                    std::getline(std::cin, input);
                    assignment_data new_assignement{current_exercice, false};
                    assignments_history.push_back(new_assignement);
                    display_grading_box();
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
            {
                std::cout << " ** Abort **" << std::endl;
                multi_sleep(1000);
            }
        }
        else
        {
            std::cout << "         **Unknown command**     type ";
            write_colored_text("help", "\x1b[38;5;46m", false);
            std::cout << " for more help" << std::endl;
        }
    }
}

void ExamSimulator::set_current_exercice()
{
    std::vector<ExerciceData> exercices = ExerciceData::get_exercices(".data/exercices.json");
    std::vector<ExerciceData> filtered_exercices = ExerciceData::get_exercises_by_level(exercices, current_level);
    ExerciceData random_ex = ExerciceData::get_random_exercice(filtered_exercices);
    current_exercice = random_ex;
    std::string home_directory = get_user_home_directory();
    std::filesystem::path ex_subject_dir = std::filesystem::path(home_directory) / "42-EXAM" / "subjects" / current_exercice.name;
    std::filesystem::create_directories(ex_subject_dir);
    std::filesystem::path old_subject_path = ".subjects/" + current_exercice.name + ".txt";
    std::filesystem::path new_subject_path = ex_subject_dir / (current_exercice.name + ".txt");
    std::filesystem::copy(old_subject_path, new_subject_path);
    std::filesystem::path renamed_subject_path = ex_subject_dir / "subject.en.txt";
    std::filesystem::rename(new_subject_path, renamed_subject_path);
}

void ExamSimulator::display_grading_box()
{
    std::cout << "==================================================================" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Mode: ";
    write_colored_text("REAL", "\x1b[38;5;13m", false);
    std::cout << " | Current Grade: ";
    write_colored_text(std::to_string(current_grade), "\x1b[38;5;46m", false);
    std::cout << " / " << std::to_string(max_grade) << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  Level ";
    write_colored_text(std::to_string(current_level), "\x1b[38;5;46m", false);
    std::cout << ":" << std::endl;
    for(size_t i = 0; i < assignments_history.size(); ++i)
    {
        write_colored_text("    " + std::to_string(assignment_index), "\x1b[38;5;11m", false);
        std::cout << ": ";
        write_colored_text(assignments_history[i].exercice.name, "\x1b[38;5;46m", false);
        std::cout << " for ";
        std::cout << std::to_string(exercice_xp);
        std::cout << " potential points (";
        write_colored_text(assignments_history[i].b_succes == true ? "Succes" : "Failure", assignments_history[i].b_succes == true ? "\x1b[38;5;46m" : "\e[91m", false);
        std::cout << ")" << std::endl;
        assignment_index++;
    }
    write_colored_text("    " + std::to_string(assignment_index), "\x1b[38;5;11m", false);
    assignment_index = 0;
    std::cout << ": ";
    write_colored_text(current_exercice.name, "\x1b[38;5;46m", false);
    std::cout << " for ";
    std::cout << std::to_string(exercice_xp);
    std::cout << " potential points (";
    write_colored_text("Current", "\e[36m", false);
    std::cout << ")" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Assignement: ";
    write_colored_text(current_exercice.name, "\x1b[38;5;46m", false);
    std::cout << " for ";
    write_colored_text(std::to_string(exercice_xp), "\x1b[38;5;46m", false);
    std::cout << "xp, try: ";
    write_colored_text("0", "\x1b[38;5;11m", true);
    std::cout << "" << std::endl;
    std::cout << "Subject location:  ";
    write_colored_text("~/42-EXAM/subjects/subject.en.txt", "\x1b[38;5;46m", true);
    std::cout << "Exercise location: ";
    write_colored_text("~/42-EXAM/rendu/" + current_exercice.name, "\e[91m", true);
    std::cout << "" << std::endl;
    std::cout << "End date: ";
    write_colored_text("21/09/2024 23:26:38", "\x1b[38;5;46m", true);
    std::cout << "Left time: ";
    write_colored_text("7hrs, 59min and 15sec", "\x1b[38;5;46m", true);
    std::cout << "" << std::endl;
    std::cout << "==================================================================" << std::endl;
    std::cout << "Use the \"";
    write_colored_text("grademe", "\x1b[38;5;46m", false);
    std::cout << "\" command to be graded, or \"";
    write_colored_text("help", "\x1b[38;5;46m", false);
    std::cout << "\" to get some help." << std::endl;
}
