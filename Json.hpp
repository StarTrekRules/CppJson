#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

struct Token {
  int type;
  string value;
};

struct JsonPair {
  string key;
  string value;
};


extern vector<Token> Tokenize(string code, string ops = "");

extern vector<JsonPair> ReadJson(string json);