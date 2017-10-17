//
// Created by izoomko on 10/18/17.
//

#include "Signal.h"


Signal::Signal(sc_module_name nm, double duty_cycle, double second_duty_cycle, double switch_time)
    : sc_module(nm),
      data_o("data_o"),
      m_duty_cycle(duty_cycle),
      m_second_duty_cycle(second_duty_cycle),
      m_switch_time(switch_time)
{
    SC_THREAD(run);
}


void Signal::run()
{
    sc_time switch_time(sc_time_stamp().to_double() + m_switch_time, SC_NS);
    while (true) {
        if (sc_time_stamp() < switch_time) {
            data_o.write(0);
            wait(500 * m_duty_cycle, SC_NS);
            data_o.write(1);
            wait(500 * (1 - m_duty_cycle), SC_NS);
            continue;
        }
        data_o.write(0);
        wait(500 * m_second_duty_cycle, SC_NS);
        data_o.write(1);
        wait(500 * (1 - m_second_duty_cycle), SC_NS);
    }
}
