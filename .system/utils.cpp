#include "utils.h"
#include "exercice_data.h"
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <thread>
#include <iomanip>


#ifdef _WIN32
#include <conio.h>
#include <shlobj.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

/* ==> The function getch return the first char in the console input without waiting a endline (\n).
If the OS is windows, you get the _getch function of termios library, and if it's linux you write this code :) <==*/
char advanced_getch() {
#ifdef _WIN32
    return _getch();
#else
    char buf = 0;
    struct termios old = { 0 };
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
#endif
}

std::string get_user_home_directory() {
#ifdef _WIN32
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path))) {
        return std::string(path);
    }
    else {
        return "";
    }
#else
    const char* home_dir = getenv("HOME");
    if (home_dir != nullptr) {
        return std::string(home_dir);
    }
    else {
        return "";
    }
#endif
}

void multi_sleep(int mili_seconds)
{
    #ifdef _WIN32
        Sleep(mili_seconds * 1000);
    #else
        usleep(mili_seconds * 1000);
    #endif
}

void write_colored_text(std::string text, std::string ansi_color, bool endline_enabled)
{
    std::cout << ansi_color;
    if (endline_enabled)
        std::cout << text << std::endl;
    else
        std::cout << text;
    std::cout << "\033[0m";
}

void write_bold_text(std::string text, bool endline_enabled)
{
    std::cout << "\033[1m";
    if (endline_enabled)
        std::cout << text << std::endl;
    else   
        std::cout << text;
    std::cout << "\033[0m";
}

void write_underlined_text(std::string text, bool endline_enabled)
{
    std::cout << "\033[4m";
    if (endline_enabled)
        std::cout << text << std::endl;
    else   
        std::cout << text;
    std::cout << "\033[0m";
}

bool compile_c_file(const std::string& file_path, const std::string& main_path)
{
    if (!std::filesystem::exists(".outputs"))
        std::filesystem::create_directories(".outputs");

    std::string command = "gcc " + file_path + " " + main_path + " -o ./.outputs/output_file 2> .outputs/compile_errors.txt";
    int result = std::system(command.c_str());

    // Vérifie si des erreurs de compilation ont été générées
    std::ifstream error_file(".outputs/compile_errors.txt");
    if (error_file.peek() != std::ifstream::traits_type::eof())
    {
        return false;
    }
    
    return result == 0;
}

std::string run_compiled_file(const std::vector<std::string>& args)
{
    std::string command = "timeout 5s ./.outputs/output_file";
    for (const auto& arg : args)
    {
        command += " \"" + arg + "\"";
    }
    command += " > .outputs/temp_output.txt";
    int result = std::system(command.c_str());
    if (result == 124)
    {
        return "TIMEOUT";
    }
    std::ifstream output_file(".outputs/temp_output.txt");
    std::stringstream buffer;
    buffer << output_file.rdbuf();
    output_file.close();
    return buffer.str();
}

int ft_atoi(const std::string str)
{
    int res;
    int i;

    res = 0;
    i = 0;

    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - 48);
        i++;
    }
    return (res);
}

bool grade_me(const std::string& exercice_name)
{
    std::vector<ExerciceData> exercices_list;
    std::string main_file;
    std::string c_file_name;

    exercices_list = ExerciceData::get_exercices(".data/exercices.json");
    c_file_name = get_user_home_directory() + "/42-EXAM/rendu/" + exercice_name + "/" + exercice_name + ".c";

    if (!std::filesystem::exists(c_file_name))
        return false;
    ExerciceData exercice = ExerciceData::get_exercice(exercice_name);
    if (exercice.is_function)
    {
        main_file = ".mains/" + exercice_name + "_main.c";
        if (compile_c_file(c_file_name, main_file))
        {
            std::string output = run_compiled_file(exercice.inputs[0]); // 0 by default because it's a function
            if (output == "S")
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
    {
        if (compile_c_file(c_file_name, main_file))
        {
            for (int i = 0; i < exercice.inputs.size(); i++)
            {
                std::string output = run_compiled_file(exercice.inputs[i]);
                if (output != exercice.outputs[i])
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}

void display_exam_end_date(std::chrono::system_clock::time_point starting_date, int exam_duration)
{
    auto date_in_x_hours = starting_date + std::chrono::hours(exam_duration);
    std::time_t time_in_x_hours = std::chrono::system_clock::to_time_t(date_in_x_hours);
    std::tm* local_time = std::localtime(&time_in_x_hours);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%d/%m/%Y %H:%M:%S");
    write_colored_text(oss.str(), "\x1b[38;5;46m", true);
}

void display_exam_left_time(std::chrono::system_clock::time_point starting_date, int exam_duration) {
    auto exam_end_time = starting_date + std::chrono::hours(exam_duration);
    auto now = std::chrono::system_clock::now();
    auto remaining_duration = exam_end_time - now;
    if (remaining_duration <= std::chrono::seconds(0)) {
        write_colored_text("Exam is over!", "\x1b[38;5;196m", true);  // Rouge pour indiquer que c'est terminé
        return;
    }
    auto hours = std::chrono::duration_cast<std::chrono::hours>(remaining_duration).count();
    remaining_duration -= std::chrono::hours(hours);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(remaining_duration).count();
    remaining_duration -= std::chrono::minutes(minutes);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(remaining_duration).count();
    std::ostringstream oss;
    oss << "Left time: " << hours << "hrs, " 
        << minutes << "min and " << seconds << "sec";
    write_colored_text(oss.str(), "\x1b[38;5;46m", true);
}
