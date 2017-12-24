//
// Created by izoomko on 10/2/17.
//
#pragma once

#include "systemc.h"

typedef unsigned short uint16_t;

SC_MODULE(Timer)
{
    enum TimerSettings
    {
        TimerInc = 0x1,
        TimerStopped = 0x2
    };

    sc_in<bool> clk_i;
    sc_in<bool> rst_i;
    sc_in<bool> en_i;
    sc_in<sc_bv<13> > addr_bi;
    sc_in<int> data_bi;
    sc_in<sc_bv<4> > we_bi;
    sc_out<uint16_t> data_bo;

    SC_CTOR(Timer);
private:
    sc_signal<uint16_t> m_tmr;
    sc_signal<uint16_t> m_tval;
    sc_signal<int> m_tconf;

    sc_signal<uint16_t> m_next_tmr;
    sc_signal<uint16_t> m_next_tval;
    sc_signal<int> m_next_tconf;

    sc_signal<int> m_next_out;

    sc_signal<bool> m_poke_timer_prev;
    sc_signal<bool> m_poke_timer_next;
    sc_signal<bool> m_poke_timer;

    void on_clock();
    void timer();
};
