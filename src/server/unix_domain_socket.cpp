#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include "unix_domain_socket.hpp"

namespace lime {
namespace server {
using namespace std;


UnixDomainSocketClient::UnixDomainSocketClient(int fd) : fd_(fd) {
}


bool UnixDomainSocketClient::Read(char* const  read_buffer,
                                  const size_t size) {
  size_t read_index = 0;
  while ((read_index == 0) ||
         (read_index < size && read_buffer[read_index-1] != '\n')) {
    const ssize_t recieved_size =
      recv(fd_, &read_buffer[read_index], size - read_index, 0);
    if (recieved_size < 0) {
      return false;
    }
    read_index += static_cast<size_t>(recieved_size);
  }
  read_buffer[read_index - 1] = '\0';
  return true;
}


bool UnixDomainSocketClient::Write(const string &response) {
  const char* const write_buffer = response.c_str();
  const size_t size = response.size();
  size_t write_index = 0;
  while (write_index != size) {
    const ssize_t sent_size = send(fd_, write_buffer + write_index, size, 0);
    if (sent_size < 0) {
      return false;
    }
    write_index += static_cast<size_t>(sent_size);
  }
  return true;
}


void UnixDomainSocketClient::Close() {
  if (fd_ < 0) {
    return;
  }
  close(fd_);
}


UnixDomainSocketAcceptor::UnixDomainSocketAcceptor(string socket_path)
  : socket_path_(socket_path) {
}


void UnixDomainSocketAcceptor::Init() {
  server_socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
  if ((server_socket_) < 0) {
    throw new runtime_error("faild to open socket\n");
  }

  int reuse_addr = 1;
  if ((setsockopt(server_socket_,
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  (const void *)&reuse_addr,
                  sizeof(reuse_addr))) < 0) {
    throw new runtime_error("faild to set socket opt\n");
  }

  remove("/tmp/lime_sock");

  struct sockaddr_un server_addr;
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, "/tmp/lime_sock");

  if (::bind(server_socket_,
             (struct sockaddr *) &server_addr,
             sizeof(server_addr)) < 0) {
    throw new runtime_error("bind() failed.");
  }

  if (listen(server_socket_, 5) < 0) {
    throw new runtime_error("listen() failed.");
  }
}


Client* UnixDomainSocketAcceptor::Accept() {
  struct sockaddr_in client_addr;
  socklen_t size = sizeof(client_addr);
  int client_socket = accept(server_socket_,
                             (struct sockaddr *) &client_addr,
                             &size);
  if (client_socket < 0) {
    return nullptr;
  }

  return new UnixDomainSocketClient(client_socket);
}


} // server
} // lime
