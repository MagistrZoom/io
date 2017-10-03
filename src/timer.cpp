//
// Created by izoomko on 10/2/17.
//

#include "timer.h"

constexpr int TIMER_INC = 0x0;
constexpr int TIMER_STOPPED = 0x1;

Timer::Timer(sc_module_name nm, int offset)
    : sc_module(nm),
      clk_i("clk_i"),
      addr_bi("addr_bi"),
      data_bi("data_bi"),
      wr_i("wr_i"),
      rd_i("rd_i"),
      data_bo("data_bo"),
      m_offset(offset)
{
    data_bo.initialize(0);

    SC_METHOD(bus_read);
    sensitive << clk_i.pos();

    SC_METHOD(tick);
    sensitive << clk_i.pos();
}

void Timer::tick() {
    if (m_tconf & TIMER_STOPPED) {
        return;
    }

    if (m_tconf & TIMER_INC)
    {
        if (m_tval < m_tmr)
        {
            m_tval++;
        }
        else
        {
            m_tval = 0;
        }
    }
    else {
        if (m_tval > 0) {
            m_tval--;
        }
        else {
            m_tval = m_tmr;
        }
    }

    data_bo.write(m_tval);
}

void Timer::bus_read()
{
    if (!rd_i.read()) {
        return;
    }

    int data = data_bi.read();
    // Align timer address on 0x0
    int addr = addr_bi.read() - m_offset;

    switch (addr) {
        case 0x0:
            m_tmr = data;
            break;
        case 0x4:
            m_tval = data;
            break;
        case 0x8:
            m_tconf = data;
            break;
    }
}
