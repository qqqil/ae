#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <vector>
#include <map>
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "logger.h"


#define AE_NONE   0
#define AE_READ   1
#define AE_WRITE  1<<1
#define AE_STOP   1<<2

class EventLoop;

typedef int file_callback(EventLoop &event_loop, int fd, void *clientData, int mask);


typedef class FileEvent {
public:
    int mask;
    file_callback *r_callback;
    file_callback *w_callback;

    void *client_data;
} aeFileEvent;
/* A fired event */
typedef struct aeFiredEvent {
    int fd;
    int mask;
} aeFiredEvent;
typedef class EventLoop {
public:
    EventLoop(int size) : set_size(size), logger("event_loop") {
        file_events = (aeFileEvent *) calloc(size, sizeof(aeFileEvent));
        if (file_events == NULL) {
            logger.error("calloc file events failed");
            exit(-1);
        }
        fired_events = (aeFiredEvent *) calloc(size, sizeof(aeFiredEvent));
        if (fired_events == NULL) {
            logger.error("calloc file events failed");
            exit(-1);
        }
    }

    ~EventLoop(){
        for(int i=0;i<1024;i++){
            if(file_events[i].mask != AE_NONE){
                close(i);
            }
        }
    }

    void ae_main();

    void process_events();

    virtual int create_event_instance();

    virtual int wait_for_event();

    int add_event(int fd, int mask, file_callback r_callback, file_callback w_callback);

    int del_event(int fd, int mask);

    virtual int add_event_intern(int fd, int mask) { return 0; };

    virtual int del_event_intern(int fd, int mask) { return 0; };
    int maxfd;
    int set_size;
    long long time_event_next_id;
    time_t last_time;

    int stop;
    void *client_data;
    aeFiredEvent *fired_events;
private:
    Logger logger;
    aeFileEvent *file_events;

} aeEventLoop;
#endif /*EVENT_LOOP_H*/
