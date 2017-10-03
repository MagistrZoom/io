//
// Created by izoomko on 10/2/17.
//

#pragma once

#include "systemc.h"
#include <vector>

SC_MODULE(BusMatrix)
{
    sc_in<bool> clk_i;
    sc_in<int> addr_bi;
    sc_in<bool> wr_i;
    sc_in<bool> rd_i;

    sc_out<bool> wr_timer1_o;
    sc_out<bool> wr_timer2_o;
    sc_out<bool> wr_ic_o;

    sc_out<bool> rd_timer1_o;
    sc_out<bool> rd_timer2_o;
    sc_out<bool> rd_ic_o;

    SC_HAS_PROCESS(BusMatrix);

    BusMatrix(sc_module_name nm);

    ~BusMatrix() = default;

private:
    std::vector<std::reference_wrapper<sc_out<bool>>> m_list;

    void select();

    void set(int device, bool read, bool write);
};