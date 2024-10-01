#pragma once

#include "option.h"
#include "exercice_data.h"
#include <vector>
#include <chrono>
#include <ctime>

class ExamSimulator : public Option
{
public:
    ExamSimulator();

    void on_select_function() override;
    void DisplayExamPage();
private:
    int current_grade;
    int current_level;
    int exercice_points;
    int max_grade;
    int attempts;
    int exs_by_level;
    int exam_duration;
    ExerciceData current_exercice;
    void set_current_exercice();
    void display_grading_box();
    struct assignment_data {
        ExerciceData exercice;
        bool b_succes;
        int level;
    };
    std::vector<assignment_data> assignments_history;
    std::chrono::system_clock::time_point starting_date;
    bool check_exam_finish(std::chrono::system_clock::time_point starting_date, int exam_duration);
};
