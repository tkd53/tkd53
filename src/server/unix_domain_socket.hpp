#pragma once

#include "server.hpp"

namespace lime {
namespace server {
using namespace std;
using namespace lime::engine;


class UnixDomainSocketClient : public Client {
public:
  UnixDomainSocketClient(int fd);

  virtual bool Read(char* const read_buffer, const size_t size) override;

  virtual bool Write(const string &response) override;

  virtual void Close() override;

private:
  int fd_;
};


class UnixDomainSocketAcceptor : public Acceptor {
public:
  UnixDomainSocketAcceptor(string socket_path);

  virtual void Init() override;

  virtual Client* Accept() override;


private:
  const string socket_path_;

  int server_socket_;
};


} // server
} // lime
