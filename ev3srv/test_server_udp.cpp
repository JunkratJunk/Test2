#include <iostream>
#include <vector>
#include <cstdio>
#include "ev3_srv_udp.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	Ev3SrvUdp srv(9999);
	srv.Start();
	for(int i=0; i<100; ++i)
	{
		srv.AddPixyData(Rect<int>(i, i+1, i+2, i+3));
	}
	std::cout << "Press any key to stop..." << std::endl;
	std::getchar();
	srv.Stop();
	return 0;
}
