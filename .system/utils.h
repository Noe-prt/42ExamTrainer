#pragma once

#include <string.h>
#include <iostream>
#include <vector>

char advanced_getch();
void write_colored_text(std::string text, std::string ansi_color, bool endline_enabled);
bool compile_c_file(const std::string& file_path, const std::string& main_path);
std::string run_compiled_file(const std::vector<std::string>& args);
bool grade_me(const std::string& exercice_name);
std::string get_user_home_directory();
void multi_sleep(int seconds);
void write_bold_text(std::string text, bool endline_enabled);
void write_underlined_text(std::string text, bool endline_enabled);