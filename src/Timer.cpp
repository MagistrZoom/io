//
// Created by izoomko on 10/2/17.
//

#include <stdlib.h>
#include "Timer.h"


Timer::Timer(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
	  rst_i("rst_i"),
	  en_i("en_i"),
      addr_bi("addr_bi"),
      data_bi("data_bi"),
      we_bi("we_bi"),
      data_bo("data_bo")
{

    SC_METHOD(on_clock);
    sensitive << clk_i.pos();
}

void Timer::on_clock()
{
	if (en_i.read()) {
	    auto data = data_bi.read();
	    auto addr = addr_bi.read();

	    switch (addr.to_int()) {
	        case 0x0:
	            m_tmr = (uint16_t) data;
	            break;
	        case 0x4:
	            m_tval = (uint16_t) data;
	            break;
	        case 0x8:
	            m_tconf = data;
	            break;
	    }
	}
	else if (rst_i.read()) {
			m_tval = 0;
			m_tmr = 0;
			m_tconf = 0;
	}
	else {
		if (!(m_tconf & TimerStopped)) { // tick arrived. Not sure about this line
			if (m_tconf & TimerInc) {
				if (m_tval < m_tmr) {
					m_tval++;
				}
				else {
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
		}
	}
	data_bo.write(m_tval);
}
