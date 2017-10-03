#include "mips32.h"
#include "mem.h"
#include "timer.h"
#include "BusMatrix.h"

int sc_main(int argc, char *argv[]) {

    sc_clock clk("clk", sc_time(10, SC_NS));
    sc_signal<int> addr;
    sc_signal<int> data_mips32_bo;
    sc_signal<int> data_mips32_bi;
    sc_signal<bool> wr;
    sc_signal<bool> rd;

    MIPS32 mips32_core("mips32");
    mips32_core.clk_i(clk);
    mips32_core.addr_bo(addr);
    mips32_core.data_bi(data_mips32_bi);
    mips32_core.data_bo(data_mips32_bo);
    mips32_core.wr_o(wr);
    mips32_core.rd_o(rd);

    BusMatrix bus("bus");
    bus.clk_i(clk);
    bus.addr_bi(addr);
    bus.wr_i(wr);
    bus.rd_i(rd);

    sc_signal<bool> wr_timer1_o,
                    wr_timer2_o,
                    wr_ic_o,
                    rd_timer1_o,
                    rd_timer2_o,
                    rd_ic_o;

    bus.wr_timer1_o(wr_timer1_o);
    bus.wr_timer2_o(wr_timer2_o);
    bus.wr_ic_o(wr_ic_o);
    bus.rd_timer1_o(rd_timer1_o);
    bus.rd_timer2_o(rd_timer2_o);
    bus.rd_ic_o(rd_ic_o);

    // Timer timer1("timer1", 0);
    // Timer timer2("timer2", 0xC);


    sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, addr, "addr");
    sc_trace(wf, wr, "wr");
    sc_trace(wf, rd, "rd");
    sc_trace(wf, wr_timer1_o, "wr_timer1_o");
    sc_trace(wf, wr_timer2_o, "wr_timer2_o");
    sc_trace(wf, wr_ic_o,     "wr_ic_o");
    sc_trace(wf, rd_timer1_o, "rd_timer1_o");
    sc_trace(wf, rd_timer2_o, "rd_timer2_o");
    sc_trace(wf, rd_ic_o,     "rd_ic_o");


    sc_start();

    sc_close_vcd_trace_file(wf);

    return (0);

}
