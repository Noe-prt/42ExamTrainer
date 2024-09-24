#pragma once

#include "option.h"
#include "exercice_data.h"

using namespace std;

class ExamSimulator : public Option
{
public:
    ExamSimulator();

    void on_select_function() override;
    void DisplayExamPage();
private:
    int current_grade;
    int current_level;
    int grade_index;
    int exercice_xp;
    int max_grade;
    ExerciceData current_exercice;
    void set_current_exercice();
};
