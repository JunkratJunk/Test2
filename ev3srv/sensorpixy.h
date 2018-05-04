#ifndef SENSORPIXY_H
#define SENSORPIXY_H
#include <vector>
#include <stdexcept>
#include <string>
#include <ev3.h>
#include <ev3_port.h>
#include <ev3_sensor.h>
#include <map>
#include <cstdlib>
#include "rect.h"


class SensorPixy
{
	uint8_t sn_;
	unsigned int sn_values_;
	public:
		SensorPixy(uint8_t sn)
			: sn_(sn)
			, sn_values_(0)
		{
			size_t err = set_sensor_mode(sn_, "SIG1");
			if (err != 4)
				std::cout << "Pixy mode not set" << std::endl;
			err = get_sensor_num_values (sn_, &sn_values_);
			if (err == 0)
				std::cout << "Zero sensor values" << std::endl;
		}
		std::pair<Rect<int>, bool> GetRect()
		{
			std::vector<int> values(sn_values_);
			size_t err = 0;
			for (unsigned int i = 0; i < sn_values_; ++i)
			{
				err = get_sensor_value(i, sn_, &values[i]);
				if (err == 0)
					std::cout << "Can not read values:" << i << std::endl;
			}
			return std::make_pair(Rect<int>(values[1], values[2], values[3], values[4]), values[0]);
		}		
};

#endif //SENSORPIXY_H