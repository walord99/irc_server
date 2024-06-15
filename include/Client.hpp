#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "global.hpp"
#include "Epoll_Wrapper.hpp"
#include "Socket.hpp"
#include "Server.hpp"

class Client : public Socket
{
public:
	Client(Server& server, Epoll_Wrapper& epoll);
	void send_msg(std::string msg);
	std::string recieve(void);
	~Client();

};

#endif