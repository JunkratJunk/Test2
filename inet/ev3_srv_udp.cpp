#include <sstream>
#include <cstring>

#include "ev3_srv_udp.h"

void Ev3SrvUdpThread(Ev3SrvUdp* obj)
{
	while(obj->is_not_stopped_)
	{
		char buf[8];
		int ret = obj->srv_.Recv(buf, 8);
		if (std::memcmp(buf, "connect", 7))
		{
			ret = obj->srv_.Send("ok", 2);
		}
		else if (std::memcmp(buf, "askpixy", 7))
		{
			std::lock_guard<std::mutex> guard(obj->mt_rects_);
			const Rect<int> r = obj->rects_.back();
			std::stringstream ss;
			ss << r.left << ", " << r.top << ", " << r.width << ", " << r.height << ";";
			ret = obj->srv_.Send(ss.str().c_str(), ss.str().size());
			obj->rects_.pop_back();
		}
	}
}

Ev3SrvUdp::Ev3SrvUdp(unsigned short port)
	: srv_(port)
	, is_not_stopped_(false)
	, t_(Ev3SrvUdpThread, this)
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

void Ev3SrvUdp::AddPixyData(const Rect<int>& r)
{
	std::lock_guard<std::mutex> guard(mt_rects_);
	rects_.push_back(r);
}

