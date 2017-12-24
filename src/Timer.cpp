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

    SC_METHOD(timer);
    sensitive << en_i
			  << m_poke_timer
			  << rst_i;
}

void Timer::timer()
{
	m_next_tmr = 0;
	m_next_tval = 0;
	m_next_tconf = 0;

	if (en_i.read()) {
	    auto data = data_bi.read();
	    auto addr = addr_bi.read();

	    switch (addr.to_int()) {
	        case 0x0:
	            m_next_tmr.write((uint16_t) data);
	            break;
	        case 0x4:
	            m_next_tval.write((uint16_t) data);
	            break;
	        case 0x8:
	            m_next_tconf.write(data);
	            break;
	    }
	}
	else if (rst_i.read()) {
			m_next_tval.write(0);
			m_next_tmr.write(0);
			m_next_tconf.write(0);
	}
	else {
		if (!(m_tconf & TimerStopped) && m_poke_timer_prev.read() != m_poke_timer.read()) { // tick arrived. Not sure about this line
		auto tval = m_tval.read();
		if (m_tconf & TimerInc) {
			if (m_tval < m_tmr) {
				m_next_tval.write(tval++);
			}
			else {
				m_next_tval.write(0);
			}
		}
		else {
			if (m_tval > 0) {
				m_next_tval.write(tval--);
			}
			else {
				m_next_tval.write(m_tmr.read());
			}
		}
		}
	}
}

void Timer::on_clock()
{
	m_tval.write(m_next_tval.read());
	m_tconf.write(m_next_tconf.read());
	m_tmr.write(m_next_tmr.read());
	data_bo.write(m_next_out.read());

	m_poke_timer_prev.write(m_poke_timer.read());
	m_poke_timer.write(!m_poke_timer.read());
}
