#include <iostream>

#include "engine/engine.hpp"
#include "converter/bigram_converter.hpp"
#include "dictionary/map_dictionary.hpp"

#include "unix_domain_socket.hpp"
#include "stdio.hpp"


using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::converter;
using namespace lime::dictionary;
using namespace lime::engine;
using namespace lime::server;


const string kNgramFreqFile = "../var/WordMarkov.freq";

const string kWordKkciMappingFile = "../var/WordKkci.text";


int main(void) {
  cerr << "Starting Kkc server"  << endl;

  shared_ptr<Bigram> bigram(new Bigram());
  bigram->Init(ifstream(kNgramFreqFile, ios::in));

  shared_ptr<MapDictionary> dict(new MapDictionary());
  dict->Init(ifstream(kWordKkciMappingFile, ios::in));

  shared_ptr<AbstractConverter> converter(new BigramConverter(bigram));

  unique_ptr<Engine> engine(new Engine(converter, dict));

  UnixDomainSocketAcceptor acceptor("/tmp/lime_sock");
  acceptor.Init();

  Server server(move(engine));
  server.Loop(&acceptor);

  return 0;
}

