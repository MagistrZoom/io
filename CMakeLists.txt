cmake_minimum_required(VERSION 3.6)
project(lab1)

include_directories(/opt/systemc-2.3.1/include)
link_directories(/opt/systemc-2.3.1/lib-linux64)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -pedantic -Wno-long-long -Wno-deprecated-declarations -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive ")

set(SOURCE_FILES
    src/main.cpp src/timer.cpp src/timer.h src/BusMatrix.cpp src/BusMatrix.h src/mips32.cpp src/mips32.h src/InputCapture.cpp src/InputCapture.h src/Prescaler.cpp src/Prescaler.h src/EdgeDetector.cpp src/EdgeDetector.h)

add_executable(lab1 ${SOURCE_FILES})
target_link_libraries(lab1 systemc m)