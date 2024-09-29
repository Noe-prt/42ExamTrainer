#pragma once

#include "option.h"
#include "exercice_data.h"
#include <vector>

class ExamSimulator : public Option
{
public:
    ExamSimulator();

    void on_select_function() override;
    void DisplayExamPage();
private:
    int current_grade;
    int current_level;
    int exercice_xp;
    int max_grade;
    int attempts;
    int ex_by_level;
    ExerciceData current_exercice;
    void set_current_exercice();
    void display_grading_box();
    struct assignment_data {
        ExerciceData exercice;
        bool b_succes;
        int level;
    };
    std::vector<assignment_data> assignments_history;
};
