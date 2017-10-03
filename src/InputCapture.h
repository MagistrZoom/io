//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"
#include "Prescaler.h"
#include "EdgeDetector.h"

SC_MODULE(InputCapture)
{
    // Bitmask
    enum CaptureFields {
        CaptureFieldsSettings = 0x7, // ICM
        CaptureFieldsBufferNonEmpty = 0x8, // ICBNE
        CaptureFieldsBufferFilled = 0x10, // ICOV
        CaptureFieldsBufferTimerMode = 0x48 // ICTMR
    };
    enum CaptureTimerSettings { // ICTMR
        CaptureTimerSettingsDisabled = 0,
        CaptureTimerSettingsTimerOne = 1,
        CaptureTimerSettingsTimerTwo = 2,
        CaptureTimerSettingsBoth     = 3
    };
    enum CaptureSettings { // ICM
       CaptureSettingsDisabled = 0x0,
       CaptureSettingsStoreAtAnyFront = 0x1,
       CaptureSettingsStoreAtFadingFront = 0x2,
       CaptureSettingsStoreAtRisingFront = 0x3,
       CaptureSettingsStoreAtForthRisingFront = 0x4,
       CaptureSettingsStoreAtSixteenthRisingFront = 0x5,
       CaptureSettingsStoreAtForthFadingFront = 0x6,
       CaptureSettingsStoreAtSixteenthFadingFront = 0x7,
    };

    sc_in<bool> clk_i;
    sc_in<int> addr_bi;
    sc_in<int> data_bi;
    sc_in<bool> wr_i;
    sc_in<bool> rd_i;
    //sc_out<int> data_bo;

    sc_in<bool> data_i;


    InputCapture(sc_module_name nm);

    ~InputCapture() = default;

private:
    int m_icconf = 0;

    sc_in<bool> prescaler_data_i;
    sc_out<bool> prescaler_data_o;
    sc_out<bool> detector_data_o;

    SC_HAS_PROCESS(InputCapture);

    Prescaler m_prescaler;
    EdgeDetector m_detector;

    void bus_read();
    void bus_write();
};

