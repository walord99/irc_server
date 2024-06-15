#include "global.hpp"
#include "Client.hpp"
#include "Epoll_Wrapper.hpp"
#include "Server.hpp"

int main(void)
{

	Epoll_Wrapper epoll;
	Server server(6969, epoll);
	std::vector<Client *> clients;

	bool cont = true;
	while (cont)
	{
		const std::vector<struct epoll_event> events = epoll.wait();
		if (events.size() != 0)
		{
			std::vector<struct epoll_event>::const_iterator ptr;
			for (ptr = events.begin(); ptr < events.end(); ptr++)
			{
				if (ptr->data.ptr == &server)
					clients.push_back(new Client(server, epoll));
				else if (ptr->events & EPOLLIN)
				{
					Client *cli = const_cast<Client *>(static_cast<const Client *>(ptr->data.ptr));
					try
					{
						std::string msg = cli->recieve();
						if (ptr->events & EPOLLOUT)
							cli->send_msg(msg);
					}
					catch (const std::exception &e)
					{
						for (size_t i = 0; i < clients.size(); i++)
						{
							if (clients[i] == cli)
								clients.erase(clients.begin() + i);

						}
						if (clients.empty() == true)
							cont = false;
					}
				}
			}
		}
	}
	for (auto &client : clients)
	{
		delete client;
	}
}
