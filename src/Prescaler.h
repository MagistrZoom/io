//
// Created by izoomko on 10/3/17.
//

#pragma once

#include "systemc.h"
#include "IDataFlowBlock.h"


SC_MODULE(Prescaler), IDataFlowBlock
{
    sc_in<bool> clk_i;
    sc_in<bool> data_i;
    sc_out<bool> data_o;

    SC_HAS_PROCESS(Prescaler);

    Prescaler(sc_module_name nm);

    ~Prescaler() = default;

    /* IDataFlowBlock */
    void set_source(IDataFlowBlock * block) override;
    void reset() override;
    void reset_chain() override;
    void enable() override;
    void enable_chain() override;

    void set_ratio(int ratio);

private:
    bool m_disabled = true;

    int m_ratio = 1;
    int m_impulse = 0;
    int m_clock = 0;
    int m_delay = 0;

    IDataFlowBlock * m_prev = nullptr;

    void process();
};

