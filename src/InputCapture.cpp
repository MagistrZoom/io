//
// Created by izoomko on 10/3/17.
//

#include <stdlib.h>
#include "InputCapture.h"


InputCapture::InputCapture(sc_module_name nm)
    : sc_module(nm),
      clk_i("clk_i"),
      addr_bi("addr_bi"),
      data_bi("data_bi"),
      wr_i("wr_i"),
      rd_i("rd_i"),
      data_bo("data_bo"),
      data_i("data_i"),
      m_detector("EdgeDetector"),
      m_prescaler("Prescaler")
{
    m_detector.clk_i(clk_i);
    m_detector.data_i(data_i);
    m_detector.data_o(detector_prescaler);

    m_prescaler.clk_i(clk_i);
    m_prescaler.data_i(detector_prescaler);
    m_prescaler.data_o(prescaler_fifo);
    m_prescaler.set_source(&m_detector);

    m_fifo.set_source(&m_prescaler);

    SC_METHOD(bus_read);
    sensitive << clk_i.pos();

    SC_METHOD(bus_write);
    sensitive << clk_i.pos();

    SC_METHOD(capture);
    sensitive << clk_i.pos();

}


void InputCapture::bus_read()
{
    if (!wr_i.read()) {
        return;
    }

    int data = data_bi.read();
    int addr = addr_bi.read();

    switch (addr) {
        case 0x18: {
            m_icconf = data;
            const auto settings = m_icconf & CaptureFieldsSettings;
            const auto timer = m_icconf & CaptureFieldsBufferTimerMode;

            int ratio = 1;
            bool enable = true;
            CaptureSettings front = CaptureSettingsStoreAtRisingFront;
            m_fifo.reset_chain();
            switch (settings) {
                case CaptureSettingsDisabled:
                    enable = false;
                    break;
                case CaptureSettingsStoreAtAnyFront:
                    front = CaptureSettingsStoreAtAnyFront;
                    break;
                case CaptureSettingsStoreAtFadingFront:
                    front = CaptureSettingsStoreAtFadingFront;
                    break;
                case CaptureSettingsStoreAtRisingFront:
                    front = CaptureSettingsStoreAtRisingFront;
                    break;
                case CaptureSettingsStoreAtForthFadingFront:
                    front = CaptureSettingsStoreAtFadingFront;
                case CaptureSettingsStoreAtForthRisingFront:
                    ratio = 4;
                    break;
                case CaptureSettingsStoreAtSixteenthFadingFront:
                    front = CaptureSettingsStoreAtFadingFront;
                case CaptureSettingsStoreAtSixteenthRisingFront:
                    ratio = 16;
                    break;
            }

            switch (timer) {
                case CaptureTimerSettingsDisabled:
                    m_timer_mode = CaptureTimerSettingsDisabled;
                    break;
                case CaptureTimerSettingsTimerOne:
                    m_timer_mode = CaptureTimerSettingsTimerOne;
                    break;
                case CaptureTimerSettingsTimerTwo:
                    m_timer_mode= CaptureTimerSettingsTimerTwo;
                    break;
                case CaptureTimerSettingsBoth:
                    m_timer_mode = CaptureTimerSettingsBoth;
                    break;
            }

            //TODO: setup FIFO
            if (enable) {
                m_detector.set_front(front);
                m_prescaler.set_ratio(ratio);
                m_fifo.enable_chain();
            }
        } break;
    }
}


void InputCapture::bus_write()
{
    //const auto rd = rd_i.read();
    //if (!m_read || rd) {
    //    m_read = rd;
    //    return;
    //}
    //m_read = rd;
    if (!rd_i.read()) {
        return;
    }

    int addr = addr_bi.read();
    switch (addr) {
        case 0x18:
            // set ICBNE
            m_icconf = (m_icconf & ~CaptureFieldsBufferNonEmpty) | ((!m_fifo.is_empty()?~0:0) & CaptureFieldsBufferNonEmpty);
            // set ICOV
            m_icconf = (m_icconf & ~CaptureFieldsBufferOverflow) | ((!m_fifo.is_full()?~0:0) & CaptureFieldsBufferOverflow);
            data_bo.write(m_icconf);
            break;
        case 0x1C: {
            const auto top = m_fifo.pop();
            data_bo.write(top);
        } break;
        default:
            abort();
            break;
    }
}


void InputCapture::capture()
{
    if (!prescaler_fifo.read() || m_timer_mode == CaptureTimerSettingsDisabled) {
        return;
    }

    switch (m_timer_mode) {
        case CaptureTimerSettingsTimerOne:
            m_fifo.push(timer1_bi.read() << sizeof(timer1_bi.read()));
            break;
        case CaptureTimerSettingsTimerTwo:
            m_fifo.push(timer2_bi.read());
            break;
        case CaptureTimerSettingsBoth:
            m_fifo.push((timer1_bi.read() << sizeof(timer1_bi.read())) | timer2_bi.read());
            break;
        default:
            abort();
            break;
    }
}
