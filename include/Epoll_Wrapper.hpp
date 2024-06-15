/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll_Wrapper.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:50:37 by bplante           #+#    #+#             */
/*   Updated: 2024/06/15 02:23:48 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EPOLL_WRAPPER_HPP
#define EPOLL_WRAPPER_HPP

#include "global.hpp"

class Epoll_Wrapper
{
private:
	int _fd;
	int _watch_count;
	std::vector<struct epoll_event> _events;
public:
	Epoll_Wrapper(void);
	void add(int fd, int events);
	void remove(int fd);
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



