
cmake_minimum_required(VERSION 3.5)
project(test2cln)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-local-typedefs -Wno-unused-result ${CMAKE_CXX_FLAGS}")

# plug OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif (OPENMP_FOUND)

#plug OpenCV
find_package(OpenCV 2.4.9 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

set(LIBS ${OpenCV_LIBRARIES})

set(SRC_CLN_CPP
    rect.h
    client_udp.h
    client_udp.cpp
    ev3_cln_udp.h
    ev3_cln_udp.cpp
    test2.cpp
    )

add_executable(test2 ${SRC_CLN_CPP})
target_link_libraries(test2 ${LIBS})

