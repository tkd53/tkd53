#pragma once

#include "engine/engine.hpp"

namespace lime {
namespace server {
using namespace std;
using namespace lime::engine;

class Client {
public:
  virtual bool Read(char* const read_buffer, const size_t size) = 0;

  virtual bool Write(const string &response) = 0;

  virtual void Close() = 0;
};

class Acceptor {
public:
  virtual void Init() = 0;

  virtual Client* Accept() = 0;
};


class Server {
public:
  Server(unique_ptr<Engine> engine);

  void Loop(Acceptor *acceptor);

private:
  bool HandleClient(Client *client);

  bool HandleRequest(const string &request_json, string *response_json);

  void HandleConvert(const KkciString &str, string *response_json);

  void HandleListCandidates(const KkciString &str, string *response_json);

  unique_ptr<Engine> engine_;
};

} // server
} // lime
