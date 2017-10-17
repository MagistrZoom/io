#include <stdlib.h>
#include "mips32.h"
#include "InputCapture.h"
#include "Timer.h"


using namespace std;


MIPS32::MIPS32(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
      addr_bo("addr_bo"),
      data_bi("data_bi"),
      data_bo("data_bo"),
      wr_o("wr_o"),
      rd_o("rd_o")
{
    addr_bo.initialize(0);
    data_bo.initialize(0);
    wr_o.initialize(0);
    rd_o.initialize(0);

    SC_CTHREAD(mainThread, clk_i.pos());
}


void MIPS32::mainThread()
{
    int impulse_posedge = 0;
    int impulse_negedge = 0;
    int next_posedge = 0;

    // static int c = 0;
    int read_n = 0;
    double ratio = 0;
    while (true) {
        switch (m_state) {
            case 0: // init
                bus_write(0x0, (uint16_t) ~0);
                bus_write(0x8, Timer::TimerInc);
                bus_write(0x18, CaptureSettingsStoreAtAnyFront | CaptureTimerSettingsTimerOne);
                m_state = 1;
                break;
            case 1: // check for ICBNE
            {
                int icconf = bus_read(0x18);
                if (icconf & CaptureFieldsBufferNonEmpty) {
                    switch (read_n) {
                        case 0:
                            m_state = 2;
                            break;
                        case 1:
                            m_state = 3;
                            break;
                        case 2:
                            m_state = 4;
                            break;
                    }
                }
                if (icconf & CaptureFieldsBufferOverflow) {
                    abort();
                }
            }
                break;
            case 2: // read impulse posedge
                impulse_posedge = next_posedge;
                m_state = 1;
                read_n = 1;
                break;
            case 3: // imp negedge
                impulse_negedge = bus_read(0x1C);
                m_state = 1;
                read_n = 2;
                break;
            case 4: { // signal end
                next_posedge = bus_read(0x1C);
                m_state = 1;
                read_n = 0;
                constexpr double epsilon = 10e-5;
                double value = (double) (next_posedge - impulse_posedge) / (impulse_negedge - impulse_posedge);
                if (std::abs(value - ratio) > epsilon && value > 0) {
                    ratio = value;
                    std::cout << "[" << sc_time_stamp() << "] duty cycle: "
                              << ratio << '\n';
                }
                if (value < 0) {
                    std::cout << "ERROR: Timer overflow probably\n";
                    sc_stop();
                    return;
                }
            }
                break;
        }

        // if (c++ == 50) {
        //     sc_stop();
        // }
        wait();
    }
}


int MIPS32::bus_read(int addr)
{
    wait();
    addr_bo.write(addr);
    rd_o.write(1);

    wait();
    rd_o.write(0);

    wait();
    int data = data_bi.read();

    return data;
}


void MIPS32::bus_write(int addr, int data)
{
    wait();
    addr_bo.write(addr);
    data_bo.write(data);
    wr_o.write(1);

    wait();
    wr_o.write(0);
}
