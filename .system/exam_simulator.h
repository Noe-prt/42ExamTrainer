#pragma once

#include "option.h"

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
    int exercice_index;
    int max_grade;
};
