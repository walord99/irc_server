/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:55:26 by bplante           #+#    #+#             */
/*   Updated: 2024/06/15 02:32:46 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "global.hpp"
#include "Epoll_Wrapper.hpp"

class Client
{
private:
	int _fd;
	Epoll_Wrapper& _epoll;
	struct sockaddr_in _cli_addr;

public:
	Client(int server_fd, Epoll_Wrapper& epoll);
	int getFD(void);
	~Client();
};

#endif