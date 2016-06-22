

#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <vector>
#include <sys/time.h>

#include "logger.h"


#define AE_NONE   0
#define AE_READ   1
#define AE_WRITE  1<<1
#define AE_STOP   1<<2
class EventLoop;

typedef void file_callback(EventLoop &event_loop,int fd,void *clientData,int mask);


typedef class aeFileEvent{
public:
  int mask;
  file_callback *f_callback;
  void *client_data;
} aeFileEvent;

typedef class EventLoop{
public:
  EventLoop(int size):set_size(size),events(size),logger("event_loop"){
    std::cout<<"event size："<<events.size()<<std::endl;
    for(auto &aefile_event : events){
        aefile_event.mask = AE_NONE;
    }
    }
  void ae_main();
  void process_events(aeFileEvent &event);
  virtual int create_event_instance();
  virtual int wait_for_event();
  int maxfd;
  int set_size;
  long long time_event_next_id;
  time_t last_time;
  std::vector<aeFileEvent> events;
  int stop;
  void *client_data;
private:
  Logger logger;
} aeEventLoop;



#endif /*EVENT_LOOP_H*/
