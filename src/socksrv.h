#pragma once
#ifndef _H_SOCKSRV_
#define _H_SOCKSRV_ 1

#include "misc.h"
#include <cmacs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

struct sockpeer
{
  int fd;
  struct sockaddr_storage addr;
};

struct descriptor socksrv (struct sockaddr *sockaddr, socklen_t sockaddrlen);

#endif /* _H_SOCKSRV_ */
