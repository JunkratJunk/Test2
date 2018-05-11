#include <vector>
#include "ev3_cln_udp.h"
#include <iostream>
#include <cstring>
#include <cstdio>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    Ev3ClnUdp cln("192.168.100.15", 9999);
    if (!cln.Connect()) 
        std::cout << "can not connect" << std::endl;
    Rect<int> rect = cln.GetPixyData();
    std::cout << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << std::endl;
    return 0;
}
