//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"


SC_MODULE(Prescaler)
{
    sc_in<bool> clk_i;
    sc_in<bool> data_i;
    sc_out<bool> data_o;

    SC_HAS_PROCESS(Prescaler);

    Prescaler(sc_module_name nm, int & inputCaptureConfig);

    ~Prescaler() = default;

private:
    int & m_icconf;
};

