#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "global.hpp"
#include "Epoll_Wrapper.hpp"

class Epoll_Wrapper;

class Socket
{
protected:
	int _fd;
	Epoll_Wrapper &_epoll;
	struct sockaddr_in _addr;

private:
	bool _is_watched;

public:
	Socket(Epoll_Wrapper& epoll);
	virtual ~Socket();
	virtual void send_msg(std::string msg) = 0;
	virtual std::string recieve(void) = 0;
	int getFD(void);

protected:
	void register_to_epoll(int events);
};

#endif
