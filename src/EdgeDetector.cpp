//
// Created by izoomko on 10/3/17.
//

#include "EdgeDetector.h"


EdgeDetector::EdgeDetector(sc_module_name nm, int & inputCaptureConf, sc_event & prescalerEvent)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o"),
      m_icconf(inputCaptureConf),
      m_prescaler_event(prescalerEvent)
{
    SC_METHOD(process);
    sensitive << clk_i.pos() << data_i.pos();
}

sc_event &
EdgeDetector::get_notifier()
{
    return m_event;
}

void
EdgeDetector::process()
{

}
