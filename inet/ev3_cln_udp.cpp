#include <sstream>
#include "ev3_cln_udp.h"

Ev3ClnUdp::Ev3ClnUdp(const char* host, unsigned short port)
	: cln_(host, port)
{

}

void Ev3ClnUdp::Connect()
{
	 cln_.Send("connect ", 8);
	 char ret[2];
	 cln_.Recv(ret, 2);
}

Rect<int> Ev3ClnUdp::GetPixyData()
{
	cln_.Send("askpixy ", 8);
	char ret[16] = "";
	cln_.Recv(ret, 16);
	int left = -1;
	int top = -1;
	int width = -1;
	int heignt = -1;
	std::stringstream ss;
	ss << ret;
	ss >> left >> top >> width >> heignt;
	return Rect<int>(left, top, width, heignt);
}
