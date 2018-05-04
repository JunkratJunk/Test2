#ifndef SERVER_UDP_H
#define SERVER_UDP_H

class ServerUdp
{
	int sockfd_;
public:
	ServerUdp(unsigned short port);
	~ServerUdp();
	int Send(const char* buffer, unsigned int size);
	int Recv(char* buffer, unsigned int size);
};

#endif // SERVER_UDP_H
