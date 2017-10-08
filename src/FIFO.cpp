//
// Created by izoomko on 10/8/17.
//

#include "FIFO.h"


FIFO::FIFO(sc_module_name nm, int & inputCaptureConfig, sc_event & detector_event)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o"),
      m_icconf(inputCaptureConfig),
      m_detector_event(detector_event)
{

}


sc_event & FIFO::get_notifier()
{
    return m_event;
}


void FIFO::process()
{

}
