#pragma once

#include "option.h"

using namespace std;

class ExamSimulator : public Option
{
public:
    ExamSimulator();

    void on_select_function() override;
};
