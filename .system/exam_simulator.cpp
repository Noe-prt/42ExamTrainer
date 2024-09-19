#include "exam_simulator.h"
#include "utils.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <pwd.h>



using namespace std;

ExamSimulator::ExamSimulator()
{
    name = "ExamSimulator";
    current_grade = 0;
    max_grade = 100;
    current_level = 0;
    exercice_index = 0;
}

void ExamSimulator::on_select_function()
{
    Option::on_select_function();
    DisplayExamPage();
}

void ExamSimulator::DisplayExamPage()
{
    std::cout << "\033[1m";
    write_underlined_text("ExamShell", true);
    std::cout << "" << std::endl;
    const char* login = getlogin();
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
    write_colored_text("ExamRank02", "\x1b[38;5;46m", false);
    write_bold_text(", in ", false);
    std::cout << "\033[1m";
    write_colored_text("REAL", "\x1b[38;5;13m", false);
    write_bold_text(" mode, at level ", false);
    std::cout << "\033[1m";
    write_colored_text("0", "\x1b[38;5;11m", false);
    write_bold_text(".", true);
    std::cout << "\033[1m";
    std::cout << "You would have ";
    write_colored_text("3hrs", "\x1b[38;5;46m", false);
    std::cout << " to complete this project." << std::endl;  
    std::cout << "\033[0m"; 
    std::cout << "Press a key to start exam 🏁" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "==================================================================" << std::endl;
    std::cout << "Mode: ";
    write_colored_text("REAL", "\x1b[38;5;13m", false);
    std::cout << " | Current Grade: ";
    write_colored_text(std::to_string(current_grade), "\x1b[38;5;46m", false);
    std::cout << " / " << std::to_string(max_grade) << std::endl;
    std::cout << "\tLevel ";
    write_colored_text(std::to_string(current_level), "\x1b[38;5;13m", false);
    std::cout << ":" << std::endl;
    write_colored_text("\t" + std::to_string(exercice_index), "\x1b[38;5;11m", false);
    std::cout << ": ";
    write_colored_text("last_word", "\x1b[38;5;46m", false);
    std::cout << "for 10 potential points (";
    write_colored_text("Current", "\x1b[38;5;14m", false);
    std::cout << ")" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Assignement: ";
    write_colored_text("last_word", "\x1b[38;5;46m", false);
    std::cout << " for ";
    write_colored_text("10", "\x1b[38;5;46m", false);
    std::cout << "xp, try: ";
    write_colored_text("0", "\x1b[38;5;13m", true);
}