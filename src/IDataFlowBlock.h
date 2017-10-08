//
// Created by izoomko on 10/14/17.
//

#pragma once

class IDataFlowBlock
{
public:
    // Link with data source
    virtual void set_source(IDataFlowBlock * block) = 0;
    // Reset data flow block
    virtual void reset() = 0;
    // Reset the block and the previous ones
    virtual void reset_chain() = 0;
    // Enable data flow block
    virtual void enable() = 0;
    // Enable the block and the previous ones
    virtual void enable_chain() = 0;
};
