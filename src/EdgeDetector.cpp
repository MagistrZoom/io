//
// Created by izoomko on 10/3/17.
//

#include <stdlib.h>
#include "EdgeDetector.h"


EdgeDetector::EdgeDetector(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o")
{
    SC_METHOD(process);
    sensitive << clk_i.pos();
}


void EdgeDetector::process()
{
    if (m_disabled) {
        return;
    }

    if (data_o.read()) {
        data_o.write(false);
    }

    const bool current = data_i.read();
    bool capture_negedge = false;
    bool capture_posedge = false;
    switch (m_front) {
        case CaptureSettingsStoreAtAnyFront:
            capture_posedge = capture_negedge = true;
            break;
        case CaptureSettingsStoreAtFadingFront:
            capture_negedge = true;
            break;
        case CaptureSettingsStoreAtRisingFront:
            capture_posedge = true;
            break;
        default:
            abort();
            break;
    }
    if ((capture_negedge && !current && m_before)
        || (capture_posedge && current && !m_before)) {
        data_o.write(true);
    }
    m_before = current;
}


void EdgeDetector::set_source(IDataFlowBlock * block)
{
    m_prev = block;
}


void EdgeDetector::reset()
{
    m_disabled = true;
    m_before = false;
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
