/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:55:12 by bplante           #+#    #+#             */
/*   Updated: 2024/06/15 02:33:02 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int server_fd, Epoll_Wrapper &epoll) : _epoll(epoll)
{
	socklen_t sock_len = sizeof(struct sockaddr_in);
	_fd = accept(server_fd, (struct sockaddr *)&_cli_addr, &sock_len);
	if (_fd == -1)
		throw new std::exception();
	try
	{
		epoll.add(_fd, EPOLLOUT | EPOLLIN);
	}
	catch (const Epoll_Wrapper::Epoll_Exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	fcntl(_fd, F_SETFL, O_NONBLOCK);
}

int Client::getFD(void)
{
	return _fd;
}

Client::~Client()
{
	_epoll.remove(_fd);
	close(_fd);
}