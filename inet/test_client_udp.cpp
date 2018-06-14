#include <vector>
#include "client_udp.h"

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	ClientUdp cln("127.0.0.1", 9999);
	cln.Send("test", 5);
	std::vector<char> buf(5);
	cln.Recv(&buf[0], 5);
	return 0;
}
