#include <cstring>
#include <iostream>

#include "stdio.hpp"

namespace lime {
namespace server {
using namespace std;


StdioClient::StdioClient(const string input) : input_(input) {
}


bool StdioClient::Read(char* const read_buffer, const size_t size) {
  if (size < input_.size()) {
    return false;
  }
  strncpy(read_buffer, input_.c_str(), input_.size());
  return true;
}


bool StdioClient::Write(const string &response) {
  cout << response << endl;
  return true;
}


void StdioClient::Close() {
}


StdioAcceptor::StdioAcceptor() {
}


void StdioAcceptor::Init() {
}


Client* StdioAcceptor::Accept() {
  string request_string;
  getline(cin, request_string);
  return new StdioClient(request_string);
}


} // server
} // lime
