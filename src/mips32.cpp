#include "mips32.h"
#include "timer.h"

using namespace std;

MIPS32::MIPS32(sc_module_name nm)
    :sc_module(nm),
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


    SC_METHOD(timer);
    sensitive << clk_i.pos();
}

MIPS32::~MIPS32()
{

}

void MIPS32::mainThread()
{
    // Configure timer

    bus_write(0x0, 25);
    bus_write(0x8, Timer::TimerInc);
}

void MIPS32::timer()
{
    static bool passed = false;
    if (data_bi.read() == 13) {
        if (passed) {
            sc_stop();
        }
        passed = true;
    }
}

int MIPS32::bus_read(int addr)
{
    int data;

    wait();
    addr_bo.write(addr);
    rd_o.write(1);
    
    wait();
    rd_o.write(0);
    
    wait();
    data = data_bi.read();
    
    cout << "MIPS32: READ " << endl;
    cout << "  -> addr: " << hex << addr << endl;
    cout << "  -> data: " << hex << data << endl;
    
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
    
    cout << "MIPS32: WRITE " << endl;
    cout << "  -> addr: " << hex << addr << endl;
    cout << "  -> data: " << hex << data << endl;

}
