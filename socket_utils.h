

#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <unistd.h>
#include <fcntl.h>

class socketUtils{

public:
	static int make_non_blocking(int sock){
		  int flags, s;

	  flags = fcntl (sock, F_GETFL, 0);
	  if (flags == -1)
	    {
	      perror ("fcntl");
	      return -1;
	    }

	  flags |= O_NONBLOCK;
	  s = fcntl (sock, F_SETFL, flags);
	  if (s == -1)
	    {
	      perror ("fcntl");
	      return -1;
	    }

	  return 0;
	}
};


#endif /*SOCKET_UTILS_H*/