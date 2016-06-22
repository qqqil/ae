#include "event_loop.h"
class EpollEventLoop:public EventLoop{
public:
  EpollEventLoop(int size):EventLoop(size),logger("epoll"){

  }
  int wait_for_event(){
    logger.info("wait for epoll event");
  }
  int create_event_instance(){
    logger.info("crete event epoll instance");
    epoll_fd = epoll_create1(0);
    if(epoll_fd == -1){
      logger.error("create epoll fd error");
      exit(-1)；
    }
  }
private:
  Logger logger;
  int epoll_fd;

};
