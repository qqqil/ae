
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include "io_file.h"

class Logger {
 public:

     Logger(const std::string &tag):_tag(tag),_file_opr(tag){
      info("crete logger for "+tag+"\n");

     }

     void logger(int log_level,const std::string &msg){
        _file_opr.write(msg+"\n");
        std::cout<<msg<<std::endl;
     }
     void info(const std::string &msg){
        logger(0,msg);
     }
     void debug(const std::string &msg){
        logger(1,msg);
     }
     void error(const std::string &msg){
        logger(2,msg);
     }

 private:
     std::string _tag;
     io_file _file_opr;
};

#endif
