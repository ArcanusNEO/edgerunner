#include "socksrv.h"

struct client
{
  struct sockpeer;
  char buffer[4096];
};

struct descriptor
socksrv (struct sockaddr *sockaddr, socklen_t sockaddrlen)
{
  signal (SIGPIPE, SIG_IGN);
  autofd int sockfd = socket (sockaddr->sa_family, SOCK_STREAM, 0);
  if (sockfd < 0)
    return (struct descriptor){ .entry = "socket < 0", .ident = errno };
  if (sockaddr->sa_family == AF_INET6
      && setsockopt (sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &(int){ 0 },
                     sizeof (int))
             < 0)
    return (struct descriptor){ .entry = "setsockopt < 0", .ident = errno };
  if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof (int))
      < 0)
    return (struct descriptor){ .entry = "setsockopt < 0", .ident = errno };
  if (bind (sockfd, sockaddr, sockaddrlen))
    return (struct descriptor){ .entry = "bind < 0", .ident = errno };
  if (listen (sockfd, 16384) < 0)
    return (struct descriptor){ .entry = "listen < 0", .ident = errno };
  for (;;)
    {
      autofd struct client client;
      client.fd = accept (sockfd, (struct sockaddr *)&client.addr,
                          &(socklen_t){ sizeof (client.addr) });
      if (client.fd < 0)
        continue;
      for (;;)
        {
          ssize_t nr = read (client.fd, client.buffer, sizeof (client.buffer));
          if (nr < 0 && errno == EINTR)
            continue;
          if (nr <= 0)
            break;
          for (ssize_t tot = 0; tot < nr;)
            {
              ssize_t nw = write (client.fd, client.buffer + tot, nr - tot);
              if (nw < 0 && errno == EINTR)
                continue;
              if (nw <= 0)
                break;
              tot += nw;
            }
        }
    }
  return (struct descriptor){ 0 };
}
