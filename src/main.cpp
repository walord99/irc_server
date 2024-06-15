/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:37:39 by bplante           #+#    #+#             */
/*   Updated: 2024/06/15 02:51:03 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"
#include "Client.hpp"
#include "Epoll_Wrapper.hpp"

int create_server_socket(sockaddr_in *serv_addr)
{
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (socket_fd < 0)
	{
		exit(1);
	}
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_addr.s_addr = INADDR_ANY;
	serv_addr->sin_port = htons(6969);

	int enable = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
	{
		std::perror("set_socket_option error");
		exit(1);
	}
	if (bind(socket_fd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) == -1)
	{
		std::perror("Binding error");
		exit(1);
	}
	if (listen(socket_fd, 128) == -1)
	{
		std::perror("listen error");
		exit(1);
	}
	return socket_fd;
}

struct epoll_event *get_fd_events(struct epoll_event *event_list, int size, int fd)
{
	for (size_t i = 0; i < size; i++)
	{
		if (event_list[i].data.fd == fd)
			return &event_list[i];
	}
	return NULL;
}

int main(void)
{
	int server_socket, new_socket_fd;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	socklen_t clilen;

	std::vector<Client *> clients;
	int epoll_list;

	server_socket = create_server_socket(&serv_addr);
	Epoll_Wrapper epoll;
	epoll.add(server_socket, EPOLLIN);
	
	char input[100];
	bool cont = true;
	while (cont)
	{
		const std::vector<struct epoll_event> events = epoll.wait();
		if (events.size() != 0)
		{
			std::vector<struct epoll_event>::const_iterator ptr;
			for (ptr = events.begin(); ptr < events.end(); ptr++)
			{
				if (ptr->data.fd == server_socket)
					clients.push_back(new Client(server_socket, epoll));
				else if (ptr->events & EPOLLIN)
				{
					char buf[100];
					ssize_t rec_size = recv(ptr->data.fd, &buf, 100, 0);
					buf[rec_size] = 0;
					if (rec_size != 0 && ptr->events & EPOLLOUT)
						send(ptr->data.fd, buf, std::strlen(buf), 0);
					else if (rec_size == 0)
						for (size_t i = 0; i < clients.size(); i++)
						{
							if (clients[i]->getFD() == ptr->data.fd)
							{
								delete clients[i];
								clients.erase(clients.begin() + i);
								if (clients.empty() == true)
									cont = false;
							}
						}
						
					else 
						std::perror("recv error");
				}
			}
		}
	}
	for (auto &client : clients)
	{
		delete client;
	}
	close(server_socket);
}
