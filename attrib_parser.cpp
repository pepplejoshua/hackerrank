#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void read_hrml(string line, map<string, map<string, string>> DICT) {
  // <tag1 value = "HelloWorld">
  // tag1: { value: "HelloWorld", .. }
}

string process_query(string q, map<string, map<string, string>> DICT) {
  return "";
}

int main() {
  // N is the number of lines of HRML program
  // Q is the number of queries that follow this program
  int N, Q;
  cin >> N >> Q;
  // skip newline character from the N Q line
  cin.ignore(1);

  // <tag1 value = "HelloWorld">
  // tag1: { value: "HelloWorld", .. }
  map<string, map<string, string>> DICT;
  vector<string> hrml;
  int _h = 0;
  for (; _h < N; _h++) {
    string line;
    getline(cin, line);
    hrml.push_back(line);
    cout << " HRML: " << line << endl;
  }

  vector<string> queries;
  int _q = 0;
  for (; _q < Q; _q++) {
    string query;
    getline(cin, query);
    queries.push_back(query);
    cout << "QUERY: " << query << endl;
  }

  for (string s : hrml) {
    read_hrml(s, DICT);
  }

  for (string q : queries) {
    cout << process_query(q, DICT) << endl;
  }
  return 0;
}
