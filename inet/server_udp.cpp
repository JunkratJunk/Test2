#include <string>
#include <stdexcept>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "server_udp.h"

ServerUdp::ServerUdp(unsigned short port)
{
	//Creating a socket
	sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd_ < 0)
		throw std::runtime_error(std::string(__FUNCTION__)+": Cannot open socket");

	//Preparing serverAddr
	struct sockaddr_in serverAddr;
	std::memset((void*)&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);
	std::memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

	//Binding on the socket
	if(bind(sockfd_, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
	{
		close(sockfd_);
		throw std::runtime_error(std::string(__FUNCTION__)+": Cannot bind socket");
	}
}

ServerUdp::~ServerUdp()
{
	close(sockfd_);
}

int ServerUdp::Send(const char* buffer, unsigned int size)
{
	struct sockaddr_in clientAddr;
	return sendto(sockfd_, buffer, size, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
}

int ServerUdp::Recv(char* buffer, unsigned int size)
{
	struct sockaddr_in clientAddr;
	socklen_t len = sizeof(clientAddr);
	return recvfrom(sockfd_, buffer, size, 0, (struct sockaddr *)&clientAddr, &len);
}
