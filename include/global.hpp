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