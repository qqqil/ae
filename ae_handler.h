
#ifndef AE_HANDLER_H
#define AE_HANDLER_H
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <regex>

static int file_read(EventLoop &event_loop,int fd,void *clientData,int mask);
static int file_write(EventLoop &event_loop,int fd,void *clientData,int mask);
static int set_sock_reuseaddr(int fd);

static int
create_and_bind (int _port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s;

  s = socket(AF_INET,SOCK_STREAM,0);
  if(s < 0){
    perror("create server socket failed");
    exit(-1);
  }
  struct sockaddr_in serv_addr;
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(_port);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
    set_sock_reuseaddr(s);
  if(bind(s,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) ==-1){
    perror("bind failed");
    exit(-1);
  }
  listen(s,64);
  return s;
}
static int
make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}

/**
 accept client connection ,and add client read/write event to event loop
**/
static int accept_handler(EventLoop &event_loop,int fd,void *clientData,int mask){
    struct sockaddr in_addr;
    socklen_t in_len;
    in_len = sizeof in_addr;

    int client = accept(fd,&in_addr,&in_len);
    if(client == -1){
      perror("accept failed");
      return -1;
    }
    int ret = make_socket_non_blocking(client);
    if(ret == -1){
      perror("make socket non blocking error");
      return -1;
    }
    ret = event_loop.add_event(client,AE_READ|AE_WRITE,file_read,file_write);
    return ret;
}
static int set_sock_reuseaddr(int fd){
    int enable = 1;
    int ret= setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&enable,sizeof(int));
    if(ret == -1){
        perror("set sock reuse address failed!");
        return -1;
    }
    return 0;
}
const char* http_end_regex="\r\n\r\n";
std::regex http_regex(http_end_regex);
bool check_is_http_end(const char* buf){
    std::string str(buf);
    return str.find("\n\n");
//    return std::regex_match(buf,http_regex);
}
/**
 *
 */
static int file_read(EventLoop &event_loop,int fd,void *clientData,int mask){
    Buffer *buffer_ptr=(Buffer *)clientData;
    int num = buffer_ptr->read(fd);
    char buf[8096];
    num = buffer_ptr->get_data(buf,8096);
    if(num >0){
        std::cout<<"read from fd:"<<fd <<":"<<buf<<std::endl;
    }else{
        return 0;
    }

    if(check_is_http_end(buf)){
        //read completed http content
        std::string response;
        std::string body="<html><head></head><body>helloworld!</body></html>";
        int len=body.length();
        response+="HTTP-Version:HTTP/1.1 200 OK\n";
        response+="Content-Type:text/html";
        response+= "Content-Length:"+std::to_string(len)+"\n";
        response+="\n\n";
        response+="<html><head></head><body>helloworld!</body></html>";
        buffer_ptr->put_data(response.c_str(),response.length());
        buffer_ptr->update_read_start(num);
    }

}
/**
 *
 */
static int file_write(EventLoop &event_loop,int fd,void *clientData,int mask){
//    std::cout<<"write data for fd:"<<fd<<std::endl;
    Buffer *buffer_ptr = (Buffer *)clientData;
    int ret = buffer_ptr->write(fd);
    return ret;
}
#endif
