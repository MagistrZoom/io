//
// Created by izoomko on 10/2/17.
//

#include "BusMatrix.h"


BusMatrix::BusMatrix(sc_module_name nm)
    : clk_i("clk"),
      addr_bi("addr_bi"),
      wr_i("wr_i"),
      rd_i("rd_i"),
      wr_timer1_o("wr_timer1_o"),
      wr_timer2_o("wr_timer2_o"),
      wr_ic_o("wr_ic_o"),
      rd_timer1_o("rd_timer1_o"),
      rd_timer2_o("rd_timer2_o"),
      rd_ic_o("rc_ic_o")
{
    wr_timer1_o.initialize(0);
    wr_timer2_o.initialize(0);
    wr_ic_o.initialize(0);
    rd_timer1_o.initialize(0);
    rd_timer2_o.initialize(0);
    rd_ic_o.initialize(0);

    m_list.emplace_back(wr_timer1_o);
    m_list.emplace_back(rd_timer1_o);
    m_list.emplace_back(wr_timer2_o);
    m_list.emplace_back(rd_timer2_o);
    m_list.emplace_back(wr_ic_o);
    m_list.emplace_back(rd_ic_o);

    SC_METHOD(select);
    sensitive << wr_i.value_changed() << rd_i.value_changed();
}


void BusMatrix::select()
{
    const auto read = rd_i.read();
    const auto write = wr_i.read();
    const auto addr = addr_bi.read();
    switch (addr) {
        case 0x0:
        case 0x4:
        case 0x8:
            set(0, read, write);
            break;
        case 0xC:
        case 0x10:
        case 0x14:
            set(1, read, write);
            break;
        case 0x18:
        case 0x1C:
            set(2, read, write);
            break;
    }
}


void BusMatrix::set(int device, bool read, bool write)
{
    device *= 2;
    for (size_t i = 0; i < m_list.size(); i++) {
        m_list[i].get().write(false);
    }
    m_list[device].get().write(write);
    m_list[device + 1].get().write(read);
}
