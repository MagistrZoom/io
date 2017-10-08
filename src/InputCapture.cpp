//
// Created by izoomko on 10/3/17.
//

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
      data_o("data_o"),
      m_prescaler("Prescaler"),
      m_detector("EdgeDetector")
//m_fifo("FIFO", m_icconf, m_detector.get_notifier())
{
    m_prescaler.clk_i(clk_i);
    m_prescaler.data_i(data_i);
    m_prescaler.data_o(prescaler_detector);

    m_detector.clk_i(clk_i);
    m_detector.data_i(prescaler_detector);
    m_detector.data_o(data_o);

    m_detector.set_source(&m_prescaler);

    SC_METHOD(bus_read);
    sensitive << clk_i.pos() << rd_i.pos();

    SC_METHOD(bus_write);
    sensitive << clk_i.pos() << wr_i.pos();

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

            int ratio = 1;
            bool enable = true;
            CaptureSettings front = CaptureSettingsStoreAtRisingFront;
            //TODO: replace to FIFO
            m_prescaler.reset_chain();
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

            if (enable) {
                m_detector.set_front(front);

                m_prescaler.set_ratio(ratio);

                //TODO: replace to FIFO
                m_detector.enable_chain();
            }
        } break;
    }
}


void InputCapture::bus_write()
{
    if (!rd_i.read()) {
        return;
    }

    int addr = addr_bi.read();
    switch (addr) {
        case 0x18:
            data_bo.write(m_icconf);
            break;
        case 0x1C:
            //TODO: FIFO top & pop
            break;
    }
}
