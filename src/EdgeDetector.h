//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"
#include "Settings.h"
#include "IDataFlowBlock.h"


SC_MODULE(EdgeDetector), public IDataFlowBlock
{
    sc_in<bool> clk_i;
    sc_in<bool> data_i;
    sc_out<bool> data_o;

    SC_HAS_PROCESS(EdgeDetector);

    EdgeDetector(sc_module_name nm);

    ~EdgeDetector() = default;

    /* IDataFlowBlock */
    void set_source(IDataFlowBlock * block) override;
    void reset() override;
    void reset_chain() override;
    void enable() override;
    void enable_chain() override;

    void set_front(CaptureSettings front);
private:
    bool m_disabled = true;
    bool m_before = false;
    CaptureSettings m_front = CaptureSettingsStoreAtRisingFront;

    IDataFlowBlock * m_prev = nullptr;

    void process();
};

