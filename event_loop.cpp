
#include <unistd.h>

#include "event_loop.h"

void EventLoop::process_events(aeFileEvent &event){
  logger.info("process event..");
  int evt_num = wait_for_event();
  if(evt_num == -1){
    logger.error("errors for waiting events");
  }
  if(evt_num > 0){

  }
}
void EventLoop::ae_main(){
    stop = 0;
    logger.info("process events");
    while(!stop){
      for(auto &aefile_event: events){
        process_events(aefile_event);
          sleep(1);
          logger.info("sleep for 1 second ..");
      }
    }
}


int EventLoop::wait_for_event(){
  
  return 0;
}

int EventLoop::create_event_instance(){

}
