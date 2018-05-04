#ifndef EV3WRP_H
#define EV3WRP_H
#include <vector>
#include <stdexcept>
#include <string>
#include <ev3.h>
#include <ev3_port.h>
#include <ev3_sensor.h>
#include <cstdlib>
 
class EV3
{
	int sz_sensor_;
	std::vector<std::string> sensor_types_;
	std::vector<std::string> sensor_names_;
	std::vector<std::string> sensor_modes_;
	public:
		EV3()
		{
			if ( ev3_init() < 1 )
				throw std::runtime_error("EV3 not init");
			find_sensors();
		}
		~EV3()
		{
			ev3_uninit();
		}
		uint8_t GetSensorPixy()
		{
			uint8_t sn_sensor;
			if ( !ev3_search_sensor( PIXY_LEGO, &sn_sensor, 0 ))
			{
				throw std::runtime_error("PIXY_LEGO is not found");
			} 
			return sn_sensor;
		}
		uint8_t GetSensorTouch()
		{
			uint8_t sn_sensor;
			if ( !ev3_search_sensor( LEGO_EV3_TOUCH, &sn_sensor, 0 ))
			{
				throw std::runtime_error("LEGO_EV3_TOUCH is not found");
			} 
			return sn_sensor;
		}		
	private:
		void find_sensors()
		{
			sz_sensor_ = ev3_sensor_init();
			if (sz_sensor_ == -1)
				throw std::runtime_error ("Sensors not found");
			for (int i = 0; i < sz_sensor_; i++ )
			{
				if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) 
				{
					sensor_types_.push_back(ev3_sensor_type( ev3_sensor[ i ].type_inx ));
					char s[ 256 ];
					ev3_sensor_port_name( i, s );
					sensor_names_.push_back(s);
					if ( get_sensor_mode( i, s, sizeof( s ))) 
					{
						sensor_modes_.push_back(s);
					}
				}
			}
		}
};

#endif //EV3WRP_H