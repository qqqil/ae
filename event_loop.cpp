
#include <unistd.h>

#include "event_loop.h"

void EventLoop::process_events(){
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
        process_events();
        sleep(1);
        logger.info("sleep for 1 second ..");
    }
}

int aeEventLoop::add_event(int fd,int mask,file_callback r_callback,file_callback w_callback){
  aeFileEvent *fe = file_events+fd;
  fe->r_callback = r_callback;
  fe->w_callback = w_callback;
  int ret = add_event_intern(fd,mask);
}
int aeEventLoop::del_event(int fd,int mask){
  int ret = del_event_intern(fd,mask);
}
int aeEventLoop::wait_for_event(){

  return 0;
}

int aeEventLoop::create_event_instance(){

}
