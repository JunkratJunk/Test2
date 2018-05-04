#ifndef CLIENT_UDP_H
#define CLIENT_UDP_H

#include <netinet/in.h>

class ClientUdp
{
	int sockfd_;
	struct sockaddr_in serverAddr_;
	struct sockaddr_in clientAddr_;
public:
	ClientUdp(const char* host, unsigned short port);
	~ClientUdp();
	int Send(const char* buffer, unsigned int size);
	int Recv(char* buffer, unsigned int size);
};

#endif // CLIENT_UDP_H
