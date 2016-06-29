#ifndef EPOLL_LOOP_H
#define EPOLL_LOOP_H

#include <sys/epoll.h>
#include "event_loop.h"

#define MAX_EVENTS 1024

class EpollEventLoop:public EventLoop{
public:
  EpollEventLoop(int size):EventLoop(size),logger("epoll"){

  }
  int wait_for_event(){
    logger.info("wait for epoll event");
    int ret;
    ret = epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
    return ret;
  }
  int create_event_instance(){
    logger.info("crete event epoll instance");
    epoll_fd = epoll_create1(0);
    if(epoll_fd == -1){
      logger.error("create epoll fd error");
      exit(-1);
    }
    return 0;
  }
  /**
  添加epoll事件
  */
  int add_event_intern(int fd,int mask){
    int ret = -1;
    struct epoll_event ee;

    ee.events |=EPOLLIN;
    ee.events |=EPOLLOUT;

    ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ee);
    if(ret == -1){
      logger.error("add epoll event failed");
      return -1;
    }
  }
  /**
   删除epoll事件
  */
  int del_event_intern(int fd,int mask){
    struct epoll_event ee;
    int ret = -1;
    ret = epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,&ee);
    if(ret == -1){
      logger.error("del epoll event failed");
      return -1;
    }
  }
private:
  Logger logger;
  int epoll_fd;
  struct epoll_event events[1024];
};

#endif /*EPOLL_LOOP_H*/
