#pragma once

#include "server.hpp"

namespace lime {
namespace server {
using namespace std;
using namespace lime::engine;


class StdioClient : public Client {
public:
  StdioClient(const string input);

  virtual bool Read(char* const read_buffer, const size_t size) override;

  virtual bool Write(const string &response) override;

  virtual void Close() override;

private:
  const string input_;
};


class StdioAcceptor : public Acceptor {
public:
  StdioAcceptor();

  virtual void Init() override;

  virtual Client* Accept() override;


private:
  const string socket_path_;

  int server_socket_;
};


} // server
} // lime
