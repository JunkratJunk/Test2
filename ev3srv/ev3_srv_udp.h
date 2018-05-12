#ifndef EV3_SRV_UDP_H
#define EV3_SRV_UDP_H

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>

#include "rect.h"
#include "server_udp.h"

class Ev3SrvUdp;
void Ev3SrvUdpThread(Ev3SrvUdp* obj);

class Ev3SrvUdp 
{
    ServerUdp srv_;
    std::queue<Rect<int>> rects_;
    std::queue<std::time_t> times_;
    std::mutex mt_rects_;
    std::atomic<bool> is_not_stopped_;
    std::thread t_;
    size_t length_;
public:
    Ev3SrvUdp(unsigned short port, size_t length);
    void Start();
    void Stop();
    void AddPixyData(const Rect<int>& r, const std::time_t& tm_c);
    friend void Ev3SrvUdpThread(Ev3SrvUdp*);
};

#endif // EV3_SRV_UDP_H
