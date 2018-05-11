#include <cstring>
#include <string>
#include <stdexcept>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "../port_reader.h"
#include "client_udp.h"

ClientUdp::ClientUdp(const char* host, unsigned short port)
{
	// Create UDP socket
	sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd_ < 0)//check UDP socket is created correctly
		throw std::runtime_error(std::string(__FUNCTION__)+": Cannot open socket");

	struct hostent *hp;
	hp = gethostbyname(host);
	if (hp == 0)//check assigment of UDP server host
	{
		close(sockfd_);
		throw std::runtime_error(std::string(__FUNCTION__)+": Cannot find host");;
	}

	// Bind any port number
	std::memset((void* )&clientAddr_, 0, sizeof(clientAddr_));
	clientAddr_.sin_family = AF_INET;
	clientAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
	clientAddr_.sin_port = htons(0);

	if (bind(sockfd_, (struct sockaddr *) &clientAddr_, sizeof(clientAddr_)) < 0)//check UDP socket is bind correctly
	{
		close(sockfd_);
		throw std::runtime_error(std::string(__FUNCTION__)+": Cannot bind socket");
	}

	std::memset((void* )&serverAddr_, 0, sizeof(serverAddr_));
	serverAddr_.sin_family = AF_INET;
	serverAddr_.sin_addr.s_addr = inet_addr(host);
	serverAddr_.sin_port = htons(port);
}

ClientUdp::~ClientUdp()
{
	close(sockfd_);
}

int ClientUdp::Send(const char* buffer, unsigned int size)
{
	socklen_t len;
	return sendto(sockfd_, buffer, size, 0, (struct sockaddr *)&serverAddr_, sizeof(serverAddr_));
}

std::vector<char> ClientUdp::Recv()
{
    return port_reader(sockfd_, (sockaddr*)&clientAddr_);
}
