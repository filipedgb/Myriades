#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>


#define IPADDRESS "127.0.0.1"
#define PORT 60070


using namespace std;

class CtoPlSocket {
public: 
	bool socketConnect();
	void envia(char *s, int len);
	void recebe(char *ans);
	void quit();
	string loop();
};

#endif