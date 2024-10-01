#pragma once

#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

char advanced_getch();
void write_colored_text(std::string text, std::string ansi_color, bool endline_enabled);
bool compile_c_file(const std::string& file_path, const std::string& main_path);
std::string run_compiled_file(const std::vector<std::string>& args);
bool grade_me(const std::string& exercice_name);
std::string get_user_home_directory();
void multi_sleep(int mili_seconds);
void write_bold_text(std::string text, bool endline_enabled);
void write_underlined_text(std::string text, bool endline_enabled);
int ft_atoi(const std::string str);
void display_exam_end_date(std::chrono::system_clock::time_point starting_date, int exam_duration);
void display_exam_left_time(std::chrono::system_clock::time_point starting_date, int exam_duration);