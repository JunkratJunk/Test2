

cmake_minimum_required(VERSION 3.0.2)
project(test2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Wno-unused-local-typedefs -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-unused-local-typedefs -Wno-unused-result")

set(LIBS ev3dev-c pthread)

set(SRC_CPP
        server_udp.h
        server_udp.cpp
        ev3_srv_udp.h
        ev3_srv_udp.cpp
        rect.h
	test2.cpp
	)

add_executable(test2 ${SRC_CPP})
target_link_libraries(test2 ${LIBS})
