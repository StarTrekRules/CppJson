#include "./Json.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Not implemented
int GetType(string value) {

  return -1;
}

// Concat to a char array using memcpy
void M_StrCat(char* ary, const char* val) {
  memcpy(ary + (sizeof(char) * strlen(ary)), val, sizeof(char));
}

// Split input into tokens
vector<Token> Tokenize(string code, string ops) {
  const char* chary = (code.append(" ")).c_str();
  
  vector<Token> toks = vector<Token>();

  char id[31];
  char str[101];
  bool instr = false;


  int len = strlen(chary) + 1;
  
  for (int i = 0; i < len; i++) {
    char c = chary[i];

    if (c == ' ') {

      if (instr) {
        M_StrCat(str, (char*) " ");
        continue;
      }

      if (strlen(id) == 0) continue;

      // Add a null terminator
      M_StrCat(id, (char*) "\0");

      Token t = Token();

      t.type = -1;
      
      t.value = id;

      toks.push_back(t);

      // Fill the array with 0(clear it)
      fill_n(id, strlen(id), 0);
      continue;
    }

    // Toggle instr variable
    if (c == '"') {

      if (instr) {
        M_StrCat(str, (char*) "\0");
        
        Token t = Token();

        t.type = 1;
      
        t.value = str;

        toks.push_back(t);

        fill_n(str, strlen(str), 0);
      }

      instr = ! instr;
      continue;
    }

    if (ops.find(c) != -1 && ! instr) {
        Token t = Token();

        t.type = 0;
        
        t.value = c;

        toks.push_back(t);

        continue;
    }
    
    if (instr)
      M_StrCat(str, &c);
    else
      strcat(id, &c);
  }

  return toks;
}

vector<JsonPair> ReadJson(string json) {
  vector<JsonPair> result = vector<JsonPair>();

  vector<Token> toks = Tokenize(json, "{:,}");

  bool opened = false;
  bool closed = false;

  char key[51];
  char val[101];
  bool keyIsSet = false;
  bool isSep = false; // If we found a :

  for (int i = 0; i < toks.capacity(); i++) {
    
    if (toks.size() == 0) {
      break;
    }

	// Get the next token
    Token t = toks.front();
    toks.erase(toks.begin());
    
    if (t.value == "{") {
      opened = true;
      continue;
    }
    else if (! opened) {
      perror (("Unexpected symbol '" + t.value + "'").c_str());
      exit(1);
    }

	// Close
    if (t.value == "}") {
      closed = true;
      continue;
    }

	// Seperate
    if (t.value == ":") {
      isSep = true;
      continue;
    }

    if (t.value == ",") continue;

    if (keyIsSet && isSep) {
      strcpy(val, (t.value + "\0").c_str());
      JsonPair pair = JsonPair();

      pair.key = key;
      pair.value = val;

      result.push_back(pair);
      keyIsSet = false;
      isSep = false;

      continue;
    }
    
    strcpy(key, (t.value + "\0").c_str());
    keyIsSet = true;
  }

  return result;
}