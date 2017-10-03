//
// Created by izoomko on 10/2/17.
//
#pragma once

#include "systemc.h"

SC_MODULE(Timer) {

    sc_in<bool> clk_i;
    sc_in<int> addr_bi;
    sc_in<int> data_bi;
    sc_in<bool> wr_i;
    sc_in<bool> rd_i;
    sc_out<int> data_bo;

    SC_HAS_PROCESS(Timer);

    Timer(sc_module_name nm, int offset);

    ~Timer() = default;
private:
    int m_offset;
    int m_tmr;
    int m_tval;
    int m_tconf;

    void bus_read();

    void tick();
};