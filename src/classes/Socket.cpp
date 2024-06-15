#include "Socket.hpp"

Socket::Socket(Epoll_Wrapper &epoll) : _epoll(epoll)
{
}

void Socket::register_to_epoll(int events)
{
	_epoll.add(*this, events);
	_is_watched = true;
}

int Socket::getFD(void)
{
	return _fd;
}

Socket::~Socket()
{
	if (_is_watched)
		_epoll.remove(*this);
	close(_fd);
}