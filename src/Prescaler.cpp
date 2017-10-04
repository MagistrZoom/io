//
// Created by izoomko on 10/3/17.
//

#include "Prescaler.h"


Prescaler::Prescaler(sc_module_name nm, int & inputCaptureConf)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o"),
      m_icconf(inputCaptureConf)
{
    SC_METHOD(process);
    sensitive << clk_i.pos() << data_i.pos();
}

sc_event &
Prescaler::get_notifier()
{
    return m_event;
}

void
Prescaler::process()
{

}
