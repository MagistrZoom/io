#include "mips32.h"
#include "Timer.h"
#include "BusMatrix.h"
#include "InputCapture.h"
#include "Signal.h"


int sc_main(int argc, char * argv[])
{
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

    sc_signal<bool> wr_timer1,
        wr_timer2,
        wr_ic,
        rd_timer1,
        rd_timer2,
        rd_ic;

    bus.wr_timer1_o(wr_timer1);
    bus.wr_timer2_o(wr_timer2);
    bus.wr_ic_o(wr_ic);
    bus.rd_timer1_o(rd_timer1);
    bus.rd_timer2_o(rd_timer2);
    bus.rd_ic_o(rd_ic);

    sc_signal<uint16_t> timer1_data;
    Timer timer1("timer1", 0);
    timer1.clk_i(clk);
    timer1.addr_bi(addr);
    timer1.data_bi(data_mips32_bo);
    timer1.data_bo(timer1_data);
    timer1.wr_i(wr_timer1);
    timer1.rd_i(rd_timer1);

    sc_signal<uint16_t> timer2_data;
    Timer timer2("timer2", 0);
    timer2.clk_i(clk);
    timer2.addr_bi(addr);
    timer2.data_bi(data_mips32_bo);
    timer2.data_bo(timer2_data);
    timer2.wr_i(wr_timer2);
    timer2.rd_i(rd_timer2);

    if (argc < 4) {
        abort();
    }
    sc_signal<bool> signal;
    double duty_cycle = std::stod(argv[1]);
    double second_duty_cycle = std::stod(argv[2]);
    double second_start = std::stod(argv[3]);
    Signal signal_block("TestSignalBlock", duty_cycle, second_duty_cycle, second_start);
    signal_block.data_o(signal);

    InputCapture capture("InputCapture");
    capture.data_i(signal);
    capture.clk_i(clk);
    capture.addr_bi(addr);
    capture.data_bi(data_mips32_bo);
    capture.data_bo(data_mips32_bi);
    capture.timer1_bi(timer1_data);
    capture.timer2_bi(timer2_data);
    capture.wr_i(wr_ic);
    capture.rd_i(rd_ic);

    sc_trace_file * wf = sc_create_vcd_trace_file("wave");
    wf->set_time_unit(100, SC_PS);
    sc_trace(wf, clk, "clk");
    sc_trace(wf, signal, "signal");
    sc_trace(wf, capture.detector_prescaler, "detector");
    sc_trace(wf, capture.prescaler_fifo, "prescaler");

    sc_trace(wf, wr_timer1, "wr_timer1");
    sc_trace(wf, wr_timer2, "wr_timer2");
    sc_trace(wf, wr_ic, "wr_ic");
    sc_trace(wf, rd_timer1, "rd_timer1");
    sc_trace(wf, rd_timer2, "rd_timer2");
    sc_trace(wf, rd_ic, "rd_ic");

    sc_trace(wf, wr, "mips_wr");
    sc_trace(wf, rd, "mips_rd");
    sc_trace(wf, data_mips32_bo, "mips_data_bo");
    sc_trace(wf, data_mips32_bi, "mips_data_bi");
    sc_trace(wf, addr, "mips_addr_bo");
    sc_start();

    sc_close_vcd_trace_file(wf);

    return 0;

}
