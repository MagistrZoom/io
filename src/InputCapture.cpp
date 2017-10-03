//
// Created by izoomko on 10/3/17.
//

#include "InputCapture.h"


InputCapture::InputCapture(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
      addr_bi("addr_bi"),
      data_bi("data_bi"),
      wr_i("wr_i"),
      rd_i("rd_i"),
      data_i("data_i"),
      m_prescaler("Prescaler", m_icconf),
      m_detector("EdgeDetector", m_icconf)
{
    m_prescaler.data_i(prescaler_data_i);
    m_prescaler.data_o(prescaler_data_o);

    m_detector.data_i(prescaler_data_o);
    m_detector.data_o(detector_data_o);

    SC_METHOD(bus_read);
    sensitive << clk_i.pos() << rd_i.pos();

    SC_METHOD(bus_write);
    sensitive << clk_i.pos() << wr_i.pos();
}

void InputCapture::bus_read()
{
    if (!wr_i.read()) {
        return;
    }

    int data = data_bi.read();
    int addr = addr_bi.read();

    switch (addr) {
        case 0x18:
            m_icconf = data;
            break;
    }
}

void InputCapture::bus_write()
{
    if (!rd_i.read()) {
        return;
    }

    int addr = addr_bi.read();
        switch (addr) {
        case 0x18:
            data_bo.write(m_icconf);
            break;
        case 0x1C:
            //TODO: FIFO top & pop
            break;
    }
}
