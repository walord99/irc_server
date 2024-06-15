#ifndef SERVER_HPP
#define SERVER_HPP

#include "Socket.hpp"
#include "global.hpp"

class Server : public Socket
{
public:
	using Socket::getFD;
	Server(short port, Epoll_Wrapper& epoll);
	~Server();
	void send_msg(std::string msg);
	std::string recieve(void);

	class Server_Exception : std::exception{
		private:
			std::string _msg;
		public:
			Server_Exception(const std::string &msg) : _msg(msg) {};
			const char* what(void) const throw() {
				return _msg.c_str();
			};
	};
};

#endif


