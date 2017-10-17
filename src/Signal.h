//
// Created by izoomko on 10/18/17.
//

#pragma once

#include "systemc.h"

SC_MODULE(Signal)
{
    sc_out<bool> data_o;

    SC_HAS_PROCESS(Signal);

    Signal(sc_module_name nm, double duty_cycle, double second_duty_cycle, double switch_time);

private:
    double m_duty_cycle = 0;
    double m_second_duty_cycle = 0;
    double m_switch_time = 0;

    void run();
};
