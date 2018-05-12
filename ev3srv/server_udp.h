#ifndef SERVER_UDP_H
#define SERVER_UDP_H
#include <vector>
#include <string>

class ServerUdp
{
    int sockfd_;
public:
    ServerUdp(unsigned short port);
    ~ServerUdp();
    int Send(const std::string& buffer);
    std::vector<char> Recv();
};

#endif // SERVER_UDP_H
