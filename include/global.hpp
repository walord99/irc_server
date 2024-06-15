/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:56:25 by bplante           #+#    #+#             */
/*   Updated: 2024/06/14 22:32:39 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "iostream"
#include "string"
#include "cstring"
#include "cstdlib"
#include "unistd.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "fcntl.h"
#include "netdb.h"
#include "sys/epoll.h"
#include "cstdio"
#include <vector>
#include "exception"

#define strerror std::string(std::strerror(errno))

#endif