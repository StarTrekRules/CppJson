#include "./Json.hpp"

// Just an example program

using namespace std;

int main() {

  vector<JsonPair> pairs = ReadJson("{ \"myKey\": \"myValue\" }");

  JsonPair top = pairs.front(); // Get the first pair

  // Output them
  cout << top.key << endl;
  cout << top.value << endl;

}