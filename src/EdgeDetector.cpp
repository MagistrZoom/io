//
// Created by izoomko on 10/3/17.
//

#include "EdgeDetector.h"


EdgeDetector::EdgeDetector(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o")
{
    SC_METHOD(process);
    sensitive << clk_i.pos() << data_i.pos() << data_i.neg();
}


void EdgeDetector::process()
{
    if (m_disabled) {
        return;
    }

    if (data_o.read()) {
        data_o.write(false);
        return;
    }

    if ((data_i.posedge() || data_i.negedge()) && m_front == CaptureSettingsStoreAtAnyFront) {
        data_o.write(true);
        return;
    }

    if (data_i.posedge() && m_front == CaptureSettingsStoreAtRisingFront) {
        data_o.write(true);
        return;
    }

    if (data_i.negedge() && m_front == CaptureSettingsStoreAtFadingFront) {
        data_o.write(true);
        return;
    }
}


void EdgeDetector::set_source(IDataFlowBlock * block)
{
    m_prev = block;
}


void EdgeDetector::reset()
{
    m_disabled = true;
    m_front = CaptureSettingsStoreAtRisingFront;
}


void EdgeDetector::reset_chain()
{
    reset();
    if (m_prev != nullptr) {
        m_prev->reset_chain();
    }
}


void EdgeDetector::enable()
{
    m_disabled = false;
}


void EdgeDetector::enable_chain()
{
    enable();
    if (m_prev != nullptr) {
        m_prev->enable_chain();
    }
}


void EdgeDetector::set_front(CaptureSettings front)
{
    m_front = front;
}
