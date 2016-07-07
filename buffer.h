#ifndef BUFFER_H
#define BUFFER_H

#include <unistd.h>
#include <iostream>
#include "logger.h"

class Buffer {
public:
    Buffer() : start_(0), end_(0), logger("buffer") {

    }

    int read(int fd) {
        int num = ::read(fd, buf + start_, 1024);
        if(num == -1){
            return -1;
        }
        std::cout << "read num:" << num << std::endl;
        end_ += num;
        if (end_ >= 8096) {
            logger.info("size of buffer is full");
            std::cout << "data:" << buf << std::endl;
            end_ = 0;
            start_ = 0;
            w_start_=0;
            w_end_ =0;
        }
        return num;
    }

    int write(int fd) {
        if(w_start_ >= w_end_){
            return 0;
        }
        int num = ::write(fd,w_buf+w_start_,w_end_-w_start_);
        if(num == -1){
            perror("write data to client failed");
            return -1;
        }
        w_start_ +=num;
        if(w_start_ == w_end_){
            w_start_ =0;
            w_end_ = 0;
        }
        return num;
    }

    int get_data(char *data, int size) {
        int num = 0;
        if(end_ -start_ > size){
            num = size;
        }else{
            num = end_ - start_;
        }
        for(int i=0;i<num;i++){
            *(data+i) = buf[start_+i];
        }
        start_ +=num;
        return num;
    }

    int put_data(char *data, int size) {
        for(int i=0;i<size;i++){
            w_buf[w_start_+i] = *(data+i);
        }
        w_end_ +=size;
        return size;
    }

    char buf[8096];
    char w_buf[8096];
    int start_;
    int end_;
    int w_start_;
    int w_end_;

private:


    Logger logger;
};


#endif /*BUFFER_H*/
