//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"
#include "Settings.h"
#include "IDataFlowBlock.h"


SC_MODULE(EdgeDetector), IDataFlowBlock
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
    CaptureSettings m_front = CaptureSettingsStoreAtRisingFront;
    bool m_disabled = true;

    IDataFlowBlock * m_prev = nullptr;

    void process();
};

