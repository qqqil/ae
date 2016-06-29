#include <iostream>

#include <string>


#include "event_loop.h"
#include "logger.h"
#include "epoll_event_loop.h"
#include "buffer.h"

#include "ae_handler.h"

Logger logger("ae");


int main(){


    logger.info("begin to start event loop..");
    EpollEventLoop epoll_event(1024);
    EventLoop &evt_loop = epoll_event;
    int port =5000;
    int server_fd = create_and_bind(&port);
    if(server_fd == -1){
      logger.error("create server and bind failed");
      exit(-1);
    }
    int ret = make_socket_non_blocking(server_fd);
    if(ret == -1){
      logger.error("make server fd non blocking failed");
      exit(-1);
    }
    std::cout<<"server fd:"<<server_fd<<std::endl;
    // aeFileEvent *fe = evt_loop.file_events+server_fd;
    // fe->mask =AE_READ;
    // fe->r_callback=accept_handler;
    evt_loop.add_event(server_fd,AE_READ,accept_handler,NULL);
    evt_loop.create_event_instance();
    evt_loop.ae_main();

    logger.info("event loop stopped!");
}
