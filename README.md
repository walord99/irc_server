# A basic irc server #

Based on the requirements of 42 school's project [ft_irc](https://github.com/walord99/irc_server/blob/main/subject/ft_irc.pdf)

TLDR: Syscalls available to use are limited to a certain set, all I/O needs to be-nonblocking and limited to 1 poll/epoll/select list. Only a certain of features and commands need to be implemented. See document for more detail. 

Even tho the document specifies the use of cpp-98, I chose to use modern cpp