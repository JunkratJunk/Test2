#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3wrp.h"
#include "sensorpixy.h"
#include <chrono>
#include <ctime>
#include "ev3_srv_udp.h"

int main()
{
	std::cout << "Waiting the EV3 brick online..." << std::endl;
        // EV3 initialization
	EV3 ev3;
        Ev3SrvUdp udp(9999);
	std::cout << "( EV3 ) Hello!" << std::endl;

	//LEGO_EV3_TOUCH opening
	uint8_t sn_touch = ev3.GetSensorTouch();
	
	//PIXY_LEGO opening
	uint8_t sn_pixy = ev3.GetSensorPixy();
        
        udp.Start();
        
        //Processing
	SensorPixy sp(sn_pixy);
	for (int i = 0; i < 1000; ++i)
	{
		std::pair<Rect<int>, bool> rect = sp.GetRect();
		std::time_t tm_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                udp.AddPixyData(rect.first);
		if (rect.second)
			std::cout << std::ctime(&tm_c) << "Rect: " << rect.first.left << ", " << rect.first.top << ", " << rect.first.width << ", " << rect.first.height << std::endl;
		else
			std::cout << std::ctime(&tm_c) << "Not rect" << std::endl;
	}
	
        udp.Stop();
	std::cout << "( EV3 ) Bye!" << std::endl;
	return EXIT_SUCCESS;
}