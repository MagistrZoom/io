//
// Created by izoomko on 10/3/17.
//

#include "InputCapture.h"


Prescaler::Prescaler(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o")
{
    SC_METHOD(process);
    sensitive << clk_i.pos();
}


void Prescaler::process()
{
    if (m_disabled) {
        return;
    }

    assert(m_ratio != 0);

    if (data_o.read()) {
        data_o.write(false);
    }

    if (data_i.read() && ++m_impulses == m_ratio) {
        data_o.write(true);
        m_impulses = 0;
    }
}


void Prescaler::set_source(IDataFlowBlock * block)
{
    m_prev = block;
}


void Prescaler::reset()
{
    m_disabled = true;
    m_ratio = 1;
    m_impulses = 0;
}


void Prescaler::reset_chain()
{
    reset();
    if (m_prev != nullptr) {
        m_prev->reset_chain();
    }
}


void Prescaler::enable()
{
    m_disabled = false;
}


void Prescaler::enable_chain()
{
    enable();
    if (m_prev != nullptr) {
        m_prev->enable_chain();
    }
}


void Prescaler::set_ratio(int ratio)
{
    m_ratio = ratio;
}
