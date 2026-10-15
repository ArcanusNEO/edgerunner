#include <socksrv.h>

int
main (int argc, char *argv[])
{
  if (argc != 3)
    goto usage;
  auto port = atol (argv[2]);
  if (port < 1 || port > 65535)
    {
      cerr ("invalid port:", argv[2]);
      return 1;
    }
  struct sockaddr *sockaddr;
  socklen_t socklen;
  union
  {
    struct sockaddr_in addr;
    struct sockaddr_in6 addr6;
  } sockun = { 0 };
  sockun.addr.sin_family = AF_INET;
  sockun.addr.sin_port = htons (port);
  if (inet_pton (AF_INET, argv[1], &sockun.addr.sin_addr) == 1)
    {
      sockaddr = (struct sockaddr *)&sockun.addr;
      socklen = sizeof (sockun.addr);
    }
  else
    {
      sockun.addr6.sin6_family = AF_INET6;
      sockun.addr6.sin6_port = htons (port);
      if (inet_pton (AF_INET6, argv[1], &sockun.addr6.sin6_addr) == 1)
        {
          sockaddr = (struct sockaddr *)&sockun.addr6;
          socklen = sizeof (sockun.addr6);
        }
      else
        {
          cerr ("invalid host:", argv[1]);
          return 1;
        }
    }
  struct descriptor result = socksrv (sockaddr, socklen);
  presult (result);
  return result.ident;
usage:
  cerr ("usage:", argv[0], "<host> <port>");
  return 1;
}
