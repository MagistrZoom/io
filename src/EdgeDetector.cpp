//
// Created by izoomko on 10/3/17.
//

#include "EdgeDetector.h"


EdgeDetector::EdgeDetector(sc_module_name nm, int & inputCaptureConf)
    : sc_module(nm),
      clk_i("clk_i"),
      data_i("data_i"),
      data_o("data_o"),
      m_icconf(inputCaptureConf)
{
}
