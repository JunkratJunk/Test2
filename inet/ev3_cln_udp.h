#ifndef EV3_CLN_UDP_H
#define EV3_CLN_UDP_H

#include "rect.h"
#include "client_udp.h"

class Ev3ClnUdp
{
	ClientUdp cln_;
public:
	Ev3ClnUdp(const char* host, unsigned short port);
	void Connect();
	Rect<int> GetPixyData();
};

#endif // EV3_CLN_UDP_H
