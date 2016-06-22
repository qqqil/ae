

#ifndef IO_FILE_H
#define IO_FILE_H
#include <fstream>
#include <string>
#include <iostream>
class io_file{
    public:

        io_file(const std::string &file_name){
            ofs.open(file_name,std::ios_base::out | std::ios_base::app);
        }
        ~io_file(){
            ofs.close();
        }
        void write(std::string data){
            ofs<<data;
        }
    private:
        std::ofstream ofs;

};

#endif
