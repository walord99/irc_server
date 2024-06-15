#ifndef EPOLL_WRAPPER_HPP
#define EPOLL_WRAPPER_HPP

#include "global.hpp"
#include "Socket.hpp"

class Socket;

class Epoll_Wrapper
{
private:
	int _fd;
	unsigned int _watch_count;
	std::vector<struct epoll_event> _events;
public:
	Epoll_Wrapper(void);
	void add(Socket& sock, int events);
	void remove(Socket& sock);
	const std::vector<struct epoll_event>& wait(void);
	~Epoll_Wrapper(void);

	class Epoll_Exception : public std::exception
	{
		private:
			std::string _message;
		public:
			Epoll_Exception(const std::string& msg) : _message(msg){};
			const char* what(void) const throw() {
				return _message.c_str();
			}
	};
};

#endif



