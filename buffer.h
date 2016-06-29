

#ifndef BUFFER_H
#define BUFFER_H

#include <unistd.h>
#include <iostream>
#include "logger.h"

class Buffer{
public:
  Buffer():start_(0),end_(0),logger("buffer"){

  }
  int read(int fd){
    int num = ::read(fd,buf+start_,1024);
    std::cout<<"read num:"<<num<<std::endl;
    return num;
  }
  int write(int fd,void *buf,size_t count){
      return ::write(fd,buf,count);
  }

  char buf[8096];
  int start_;
  int end_;
private:


  Logger logger;
};

#endif /*BUFFER_H*/
