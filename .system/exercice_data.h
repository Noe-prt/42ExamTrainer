#pragma once

#include <iostream>
#include <string>
#include <vector>

class ExerciceData
{
public:
    std::string name;
    int level;
    bool is_function;
    std::vector<std::vector<std::string>> inputs;
    std::vector<std::string> outputs;
    static std::vector<ExerciceData> get_exercices(const std::string& filename);
    static ExerciceData get_exercice(const std::string& exercice_name);
    static std::vector<ExerciceData> get_exercises_by_level(const std::vector<ExerciceData>& exercises, int level);
    static ExerciceData get_exercice_by_index(int ex_index);
};