#include <sstream>
#include <vector>
#include <cstring>
#include <ctime>
#include "ev3_cln_udp.h"

Ev3ClnUdp::Ev3ClnUdp(const char* host, unsigned short port)
	: cln_(host, port)
{

}

bool Ev3ClnUdp::Connect()
{
	int x = cln_.Send("connect;", 8);
    std::vector<char> ret = cln_.Recv();
    return std::memcmp(&ret[0], "ok;", 3)==0;
}

Rect<int> Ev3ClnUdp::GetPixyData()
{
	cln_.Send("askpixy;", 8);
        std::vector<char> ret = cln_.Recv();
	int left = -1;
	int top = -1;
	int width = -1;
	int heignt = -1;
        std::time_t tm = 0;
	std::stringstream ss;
        std::string ttt (ret.begin(), ret.end());
	ss << ttt;
	ss >> tm >> left >> top >> width >> heignt;
	return Rect<int>(left, top, width, heignt);
}
