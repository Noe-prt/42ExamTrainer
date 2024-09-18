#include "exam_simulator.h"
#include <iostream>

using namespace std;

ExamSimulator::ExamSimulator()
{
    name = "ExamSimulator";
}

void ExamSimulator::on_select_function()
{
    Option::on_select_function();
    cout << "Coming soon..." << endl;
}