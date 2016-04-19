#include <gtest/gtest.h>
#include <iostream>
#include "dictionary/map_dictionary.hpp"
#include "converter/bigram_converter.hpp"
#include "engine.hpp"

using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::converter;
using namespace lime::dictionary;
using namespace lime::engine;


namespace {

void testConvert(Engine *engine,
                 const vector<KkciString> &inputs,
                 const vector<TokenString> &expected_tokenstrings) {
  for (size_t i = 0; i < inputs.size(); i++) {
    deque<Node> actual;
    engine->Convert(inputs[i], &actual);
    const TokenString &expected = expected_tokenstrings[i];

    ASSERT_EQ(expected.size(), actual.size());
    for (size_t j = 0; j < actual.size(); j++) {
      ASSERT_EQ(expected[j], actual[j].token);
    }
  }
}

} // namespace


class EngineTestBase : public ::testing::Test {
protected:
  Engine *engine_;

  vector<KkciString> inputs_;

  vector<TokenString> expected_tokenstrings_;

  void SetUp() override {
    // し ょ う ぎ の ほ ん
    inputs_.push_back(KkciString({58, 106, 41, 49, 81, 94, 118}));
    // 将棋 の 本
    expected_tokenstrings_.push_back(TokenString({14686, 2461, 21867}));

    // こ う じ ち ゅ う
    inputs_.push_back(KkciString({54, 41, 59, 68, 104, 41}));
    // 工事 中
    expected_tokenstrings_.push_back(TokenString({11753, 18060}));
  }
};


class EngineWithBigramConverterTest : public EngineTestBase {
protected:
  void SetUp() override {
    EngineTestBase::SetUp();

    shared_ptr<Bigram> bigram(new Bigram());
    bigram->Init(ifstream("../../../var/WordMarkov.freq", ios::in));

    shared_ptr<MapDictionary> dict(new MapDictionary());
    dict->Init(ifstream("../../../var/WordKkci.text", ios::in));

    engine_ = new Engine(shared_ptr<BigramConverter>(
        new BigramConverter(bigram)), dict);
  }
};


TEST_F(EngineWithBigramConverterTest, Convert) {
  testConvert(engine_, inputs_, expected_tokenstrings_);
}
