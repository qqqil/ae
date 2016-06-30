
#ifndef AE_HANDLER_H
#define AE_HANDLER_H
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


static int
create_and_bind (int *_port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
  hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
  hints.ai_flags = AI_PASSIVE;     /* All interfaces */
  char port;
  s = getaddrinfo (NULL, &port, &hints, &result);
  if (s != 0)
    {
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      return -1;
    }

  for (rp = result; rp != NULL; rp = rp->ai_next)
    {
      sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
      if (sfd == -1)
        continue;

      s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
      if (s == 0)
        {
          /* We managed to bind successfully! */
          break;
        }

      close (sfd);
    }

  if (rp == NULL)
    {
      fprintf (stderr, "Could not bind\n");
      return -1;
    }

  freeaddrinfo (result);

  return sfd;
}
static int
make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}

/**
 accept client connection ,and add client read/write event to event loop
**/
static int accept_handler(EventLoop &event_loop,int fd,void *clientData,int mask){
    struct sockaddr in_addr;
    socklen_t in_len;
    in_len = sizeof in_addr;

    int client = accept(fd,&in_addr,&in_len);
    if(client == -1){
      perror("accept failed");
      return -1;
    }
    int ret = make_socket_non_blocking(client);
    if(ret == -1){
      perror("make socket non blocking error");
      return -1;
    }
    ret = event_loop.add_event(client,AE_READ|AE_WRITE,fire_read,file_write);
    return ret;
}

static int file_read(EventLoop &event_loop,int fd,void *clientData,int mask){

}
static int file_write(EventLoop &event_loop,int fd,void *clientData,int mask){

}
#endif
