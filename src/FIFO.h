//
// Created by izoomko on 10/8/17.
//
#include "systemc.h"


SC_MODULE(FIFO)
{
    sc_in<bool> clk_i;
    sc_in<bool> data_i;
    sc_out<int> data_o;

    SC_HAS_PROCESS(FIFO);

    FIFO(sc_module_name nm, int & inputCaptureConfig, sc_event & detector_event);

    ~FIFO() = default;

    sc_event & get_notifier();
private:
    int & m_icconf;

    sc_event m_event;
    sc_event & m_detector_event;

    void process();
};

