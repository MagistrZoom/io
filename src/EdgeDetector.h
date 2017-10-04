//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"


SC_MODULE(EdgeDetector)
{
    sc_in<bool> clk_i;
    sc_in<bool> data_i;
    sc_out<bool> data_o;

    SC_HAS_PROCESS(EdgeDetector);

    EdgeDetector(sc_module_name nm, int & inputCaptureConfig, sc_event & prescaler_event);

    ~EdgeDetector() = default;

    sc_event & get_notifier();
private:
    int & m_icconf;

    sc_event m_event;
    sc_event & m_prescaler_event;

    void process();
};

