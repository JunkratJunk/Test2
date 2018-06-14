
cmake_minimum_required(VERSION 3.5)
project(inet)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-local-typedefs -Wno-unused-result ${CMAKE_CXX_FLAGS}")

#plug Boost
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.58 COMPONENTS
    system
    graph
    unit_test_framework
    program_options
    log
    REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# plug OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif (OPENMP_FOUND)

# plug GTK2
find_package(GTK2)

# plug FFmpeg
set(FFMPEG_USE_STATIC_LIBS ON)
find_package(FFmpeg REQUIRED)

#plug OpenCV
find_package(OpenCV 3.2.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

set(LIBS ${FFMPEG_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} ${GTK2_LIBRARIES})

set(SRC_SRV_CPP
    rect.h
    server_udp.h
    server_udp.cpp
    ev3_srv_udp.h
    ev3_srv_udp.cpp
    test_server_udp.cpp
    )

set(SRC_CLN_CPP
    rect.h
    client_udp.h
    client_udp.cpp
    ev3_cln_udp.h
    ev3_cln_udp.cpp
    test_client_udp.cpp
    )

add_executable(server_udp ${SRC_SRV_CPP})
target_link_libraries(server_udp ${LIBS})

add_executable(client_udp ${SRC_CLN_CPP})
target_link_libraries(client_udp ${LIBS})

