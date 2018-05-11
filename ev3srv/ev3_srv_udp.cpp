#include <sstream>
#include <cstring>
#include <iostream>
#include "ev3_srv_udp.h"

void Ev3SrvUdpThread(Ev3SrvUdp* obj)
{
	while(obj->is_not_stopped_)
	{
		char buf[7];
		int ret = obj->srv_.Recv(buf, 7);
                std::cout << "recv from client " << ret << std::endl;
                for (size_t i=0, ie=7; i<ie; ++i)
                    std::printf("%c", buf[i]);
                std::cout << std::endl;
		if (std::memcmp(buf, "connect", 7))
		{
			ret = obj->srv_.Send("ok", 2);
		}
		else if (std::memcmp(buf, "askpixy", 7))
		{
			std::lock_guard<std::mutex> guard(obj->mt_rects_);
			const Rect<int> r = obj->rects_.front();
                        const std::time_t t = obj->times_.front();
			std::stringstream ss;
			ss << t << ", " << r.left << ", " << r.top << ", " << r.width << ", " << r.height << ";";
			ret = obj->srv_.Send(ss.str().c_str(), ss.str().size());
			obj->rects_.pop();
		}
	}
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

