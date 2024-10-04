#include "exercice_data.h"
#include <fstream>
#include <algorithm>
#include <random>
#include<nlohmann/json.hpp>

std::vector<ExerciceData> ExerciceData::get_exercices(const std::string& filename)
{
    std::ifstream file(filename);
    nlohmann::json jsonData;
    file >> jsonData;

    std::vector<ExerciceData> exercises;

    for (const auto& item : jsonData["exercices"]) {
        ExerciceData ex;
        ex.name = item["name"].get<std::string>();
        ex.level = item["level"].get<int>();
        ex.sub_level = item["sub_level"].get<int>();
        ex.is_function = (item["type"].get<std::string>() == "function");
        ex.inputs = item["inputs"].get<std::vector<std::vector<std::string>>>();
        ex.outputs = item["outputs"].get<std::vector<std::string>>();
        exercises.push_back(ex);
    }

    return exercises;
}

std::vector<ExerciceData> ExerciceData::get_exercises_by_level(const std::vector<ExerciceData>& exercises, int level)
{
    std::vector<ExerciceData> filtered_exercices;
    
    std::copy_if(exercises.begin(), exercises.end(), std::back_inserter(filtered_exercices),
        [level](const ExerciceData& ex)
        {
            return ex.level == level;
        }
    );
    return filtered_exercices;
}

std::vector<ExerciceData> ExerciceData::get_exercises_by_sub_level(const std::vector<ExerciceData>& exercises, int sub_level)
{
    std::vector<ExerciceData> filtered_exercices;
    
    std::copy_if(exercises.begin(), exercises.end(), std::back_inserter(filtered_exercices),
        [sub_level](const ExerciceData& ex)
        {
            return ex.sub_level == sub_level;
        }
    );
    return filtered_exercices;
}

ExerciceData ExerciceData::get_exercice_by_index(int ex_index)
{
    int i = 1;
    std::vector<ExerciceData> exercices = ExerciceData::get_exercices(".data/exercices.json");
    for (auto& ex : exercices)
    {
        if (i == ex_index)
            return ex;
        i++;
    }
    throw std::runtime_error("invalid index ! Please try again");
}

ExerciceData ExerciceData::get_exercice(const std::string& exercice_name)
{
    std::vector<ExerciceData> exercices = ExerciceData::get_exercices(".data/exercices.json");
    for (const auto& ex : exercices)
    {
        if (ex.name == exercice_name)
            return ex;
    }
    throw std::runtime_error("Exercice not found: " + exercice_name);
}

ExerciceData ExerciceData::get_random_exercice(const std::vector<ExerciceData>& exercices)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, exercices.size() - 1);
    int random_index = distrib(gen);
    return exercices[random_index];
}