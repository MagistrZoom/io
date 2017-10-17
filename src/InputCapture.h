//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"
#include "Settings.h"
#include "Prescaler.h"
#include "EdgeDetector.h"
#include "FIFO.h"


SC_MODULE(InputCapture)
{
    sc_in<bool> clk_i;
    sc_in<int> addr_bi;
    sc_in<int> data_bi;
    sc_in<bool> wr_i;
    sc_in<bool> rd_i;
    sc_out<int> data_bo;

    sc_in<uint16_t> timer1_bi;
    sc_in<uint16_t> timer2_bi;

    sc_in<bool> data_i;

    SC_HAS_PROCESS(InputCapture);

    InputCapture(sc_module_name nm);

    ~InputCapture() = default;

    sc_signal<bool> detector_prescaler;
    sc_signal<bool> prescaler_fifo;

private:
    int m_icconf = 0;

    bool m_read = false;

    EdgeDetector m_detector;
    Prescaler m_prescaler;

    CaptureTimerSettings m_timer_mode = CaptureTimerSettingsDisabled;
    FIFO<16> m_fifo;

    void bus_read();
    void bus_write();
    void capture();
};

