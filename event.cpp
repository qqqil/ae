#include <iostream>

#include <string>


#include "event_loop.h"
#include "logger.h"
#include "epoll_event_loop.h"

int main(){

    Logger logger("ae");
    logger.info("begin to start event loop..");
    EpollEventLoop epoll_event(1024);
    EventLoop &evt_loop = epoll_event;
    evt_loop.create_event_instance();
    evt_loop.ae_main();

    logger.info("event loop stopped!");
}
