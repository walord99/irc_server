#include "Client.hpp"

Client::Client(Server& server, Epoll_Wrapper &epoll) : Socket(epoll)
{
	socklen_t sock_len = sizeof(struct sockaddr_in);
	_fd = accept(server.getFD(), (struct sockaddr *)&_addr, &sock_len);
	if (_fd == -1)
		throw new std::exception();
	register_to_epoll(EPOLLIN | EPOLLOUT);
	fcntl(_fd, F_SETFL, O_NONBLOCK);
}

Client::~Client()
{
}

void Client::send_msg(std::string msg)
{
	send(_fd, msg.c_str(), msg.size(), 0);
}

std::string Client::recieve(void)
{
	char buf[50];
	int rec_len = recv(_fd, buf, 50, 0);
	if (rec_len == 0)
	{
		delete this;
		throw std::exception();
	}
	return std::string(buf);
}