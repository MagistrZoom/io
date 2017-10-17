//
// Created by izoomko on 10/8/17.
//
#include <stdlib.h>
#include "systemc.h"
#include "IDataFlowBlock.h"
#include "Settings.h"


template<uint32_t SIZE>
struct FIFO
    : public IDataFlowBlock
{
    FIFO() = default;
    ~FIFO() = default;

    /* IDataFlowBlock */
    void set_source(IDataFlowBlock * block) override
    {
        m_prev = block;
    }

    void reset() override
    {
        m_disabled = true;
        m_size = 0;
    }

    void reset_chain() override
    {
        reset();
        if (m_prev != nullptr) {
            m_prev->reset_chain();
        }
    }

    void enable() override
    {
        m_disabled = false;
    }

    void enable_chain() override
    {
        enable();
        if (m_prev != nullptr) {
            m_prev->enable_chain();
        }
    }

    uint32_t pop()
    {
        if (is_empty()) {
            return 0;
        }
        const auto value = m_fifo[0];
        memcpy(m_fifo, &m_fifo[1], sizeof(value) * m_size);
        m_size--;
        return value;
    }

    void push(uint32_t value)
    {
        if (m_disabled || is_full()) {
            return;
        }

        m_fifo[m_size++] = value;
    }

    bool is_empty()
    {
        return m_size == 0;
    }

    bool is_full()
    {
        return m_size == SIZE;
    }

private:
    bool m_disabled = true;

    uint32_t m_fifo[SIZE] = {0};
    uint32_t m_size = 0;

    IDataFlowBlock * m_prev = nullptr;
};

