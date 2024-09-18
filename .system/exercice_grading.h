#pragma once

#include "option.h"
#include "exercice_data.h"

using namespace std;

class ExerciceGrading : public Option
{
public:
    ExerciceGrading();

    void on_select_function() override;
private:
    std::vector<ExerciceData> exercices_list;
    void display_exercices();
    void display_grading_page(ExerciceData exercice);
    void display_subject(const std::string& file_path);
    ExerciceData get_selected_exercice();
};
