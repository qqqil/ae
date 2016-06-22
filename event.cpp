#include <iostream>

#include <string>


#include "event_loop.h"
#include "logger.h"






int main(){

    Logger logger("ae");
    logger.info("begin to start event loop..");

    EventLoop event_loop(1024);

    event_loop.ae_main();

    logger.info("event loop stopped!");
}
