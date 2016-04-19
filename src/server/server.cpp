#include <iostream>
#include <sstream>

#include <picojson/picojson.h>

#include "server.hpp"

namespace lime {
namespace server {
using namespace std;

namespace {
void PerrorAndExit(string msg) {
  cerr << msg << endl;
  exit(1);
}


void ReadKkciString(picojson::array &kkci_seq, KkciString *str) {
  for (picojson::array::iterator it = kkci_seq.begin();
       it != kkci_seq.end(); ++it) {
    str->push_back(static_cast<Kkci>(it->get<double>()));
  }
}

class ScopedCloser {
public:
  ScopedCloser(Client *client) : client_(client) {
  }

  ~ScopedCloser() {
    client_->Close();
  }
private:
  Client *client_;
};


} // namespace



Server::Server(unique_ptr<Engine> engine) : engine_(move(engine)) {
}


void Server::Loop(Acceptor *acceptor) {
  Client *client;
  while ((client = acceptor->Accept()) != nullptr) {
    ScopedCloser closer(client);
    cout << "Processing new connection" << endl;
    HandleClient(client);
    cout << "close client" << endl;
  }
}


bool Server::HandleClient(Client *client) {
  char read_buffer[1024];

  if (!client->Read(read_buffer, sizeof(read_buffer))) {
    PerrorAndExit("read() failed.");
  }

  cerr << "Request: " << read_buffer <<  endl;

  string response_json;
  if (!HandleRequest(string(read_buffer), &response_json)) {
    return false;
  }

  cerr << "Response: " << response_json;

  if (!client->Write(response_json)) {
    PerrorAndExit("write() failed.");
  }

  return true;
}


bool Server::HandleRequest(const string &request_json,
                           string *response_json) {
  string err;
  picojson::value v;
  picojson::parse(v, request_json);

  if (!err.empty()) {
    *response_json = "{\"result\":false, \"message\":\"invalid json\"}";
    return true;
  }

  picojson::object &obj = v.get<picojson::object>();
  const string &command = obj["command"].get<string>();
  if (command == "CONVERT") {
    KkciString str;
    ReadKkciString(obj["kkciSequence"].get<picojson::array>(), &str);
    HandleConvert(str, response_json);
    return true;
  }

  if (command == "LIST_CANDIDATES") {
    KkciString str;
    ReadKkciString(obj["kkciSequence"].get<picojson::array>(), &str);
    HandleListCandidates(str, response_json);
    return true;
  }

  return false;
}


void Server::HandleConvert(const KkciString &str, string *response_json) {
  deque<Node> nodes;
  engine_->Convert(str, &nodes);

  stringstream ss;
  ss << "{\"result\":true,\"kkciSequence\":[";
  for (size_t i = 0; i < nodes.size(); i++) {
    if (0 < i) {
      ss << ",";
    }
    ss << "{";
    ss << "\"token\":" << nodes[i].token;
    ss << ",\"origin\":" << nodes[i].entry->origin;
    ss << ",\"kkciSequence\":[";
    for (size_t j = 0; j < nodes[i].entry->kkci_string.size(); j++) {
      if (0 < j) {
        ss << ",";
      }
      ss << nodes[i].entry->kkci_string[j];
    }
    ss << "]}";
  }
  ss << "]}" << endl;
  *response_json = ss.str();
}


void Server::HandleListCandidates(const KkciString &str,
                                  string *response_json) {
  vector<const Entry*> output;
  engine_->ListCandidates(str, &output);

  stringstream ss;
  ss << "{\"result\":true,\"kkciSequence\":[";
  for (size_t i = 0; i < output.size(); i++) {
    if (0 < i) {
      ss << ",";
    }
    ss << "{";
    ss << "\"token\":" << output[i]->token;
    ss << ",\"origin\":" << output[i]->origin;
    ss << ",\"kkciSequence\":[";
    for (size_t j = 0; j < output[i]->kkci_string.size(); j++) {
      if (0 < j) {
        ss << ",";
      }
      ss << output[i]->kkci_string[j];
    }
    ss << "]}";
  }
  ss << "]}" << endl;
  *response_json = ss.str();
}


} // server
} // lime
