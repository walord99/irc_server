/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll_Wrapper.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:50:24 by bplante           #+#    #+#             */
/*   Updated: 2024/06/15 02:45:52 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Epoll_Wrapper.hpp"

Epoll_Wrapper::Epoll_Wrapper(void) : _watch_count(0)
{
	_fd = epoll_create(1);
	_events.reserve(5);
	if (_fd == -1)
		throw Epoll_Exception("epoll_create() error: " + strerror);
}

void Epoll_Wrapper::add(int fd, int events)
{
	struct epoll_event ep;
	ep.data.fd = fd;
	ep.events = events;
	if (epoll_ctl(_fd, EPOLL_CTL_ADD, fd, &ep) == -1)
		throw Epoll_Exception("epoll_ctl() add error: " + strerror);
	_watch_count++;
	if(_events.capacity() < _watch_count)
		_events.reserve(_watch_count * 2);
}

void Epoll_Wrapper::remove(int fd)
{
	if (epoll_ctl(_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
		throw Epoll_Exception("epoll_ctl() del error: " + strerror);
	_watch_count--;
	if (_events.capacity() / 2 > _watch_count)
		_events.shrink_to_fit();
}

const std::vector<struct epoll_event>& Epoll_Wrapper::wait(void)
{
	_events.resize(_watch_count);
	int event_count = epoll_wait(_fd, &_events[0], _watch_count, 0);
	if (event_count == -1)
		throw Epoll_Exception("epoll_wait() error: " + strerror);
	_events.resize(event_count);
	return _events;
}

Epoll_Wrapper::~Epoll_Wrapper(void)
{
	close(_fd);
}