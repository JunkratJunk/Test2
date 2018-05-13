#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include "ev3_srv_udp.h"

void Ev3SrvUdpThread(Ev3SrvUdp* obj)
{
	while (obj->is_not_stopped_)
	{
		std::cout << "spinning" << obj << std::endl;
		std::vector<char> ret = obj->srv_.Recv();
		std::string t(ret.begin(), ret.end());
		std::cout << "recv from client " << t << std::endl;
		if (std::memcmp(&ret[0], "connect", 7))
		{
			int ret = obj->srv_.Send("ok;");
		}
		else if (std::memcmp(&ret[0], "askpixy", 7))
		{
			std::lock_guard<std::mutex> guard(obj->mt_rects_);
			const Rect<int> r = obj->rects_.front();
			const std::time_t t = obj->times_.front();
			std::stringstream ss;
			ss << t << ", " << r.left << ", " << r.top << ", " << r.width << ", " << r.height << ";";
			int ret = obj->srv_.Send(ss.str());
			obj->rects_.pop();
		}
	}
	std::cout << "exit_thread" << std::endl;
}

Ev3SrvUdp::Ev3SrvUdp(unsigned short port, size_t length)
: srv_(port)
, is_not_stopped_(false)
, t_(Ev3SrvUdpThread, this)
, length_(length)
{

}

void Ev3SrvUdp::Start()
{
	is_not_stopped_ = true;
}

void Ev3SrvUdp::Stop()
{
	is_not_stopped_ = false;
	t_.join();
}

void Ev3SrvUdp::AddPixyData(const Rect<int>& r, const std::time_t& tm_c)
{
	std::lock_guard<std::mutex> guard(mt_rects_);
	rects_.push(r);
	if (rects_.size() == length_)
		rects_.pop();
	times_.push(tm_c);
	if (times_.size() == length_)
		times_.pop();
}

