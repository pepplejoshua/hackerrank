#include <cmath>
#include <cstdio>
#include <map>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

void read_hrml(string line, map<string, map<string, string>> DICT) {
  // <tag1 value = "HelloWorld">
  // tag1: { value: "HelloWorld", .. }
  int loc = 0;

  assert(line[loc] == '<');
  loc++;

  if (line[loc] == '/') {
    // we are in a closing tag, so we can just read the name and >
    loc++;
    char ch = line[loc];
    string tag = "";
    while (ch != '>') {
      tag += ch;
      loc++;
      ch = line[loc];
    }
    loc++; // go to newline
    assert(line.size() == loc);
  } else {
    char ch = line[loc];
    string tag = "";
    while (ch != '>' && ch != ' ') {
      tag += ch;
      loc++;
      ch = line[loc];
    }

    if (ch == '>') {
      // there are no attributes
      DICT[tag] = map<string, string>();
      loc++; // go to newline
      assert(line.size() == loc);
    } else {
      // there are attributes to read:
      // attribName = "value">
      // attribName2="value" ..>
      loc++; // go to start of attribute name

      while (ch != '>') {
        string attribName = "";
        ch = line[loc];
        while (ch != '=' && ch != ' ') {
          attribName += ch;
          loc++;
          ch = line[loc];
        }
        bool was_spaced = false;
        if (ch == ' ') {
          loc++; // move to the =
          was_spaced = true;
        }

        loc++; // move past the =
        if (was_spaced) {
          loc++; // move past the space after the =
        }

        assert(line[loc] == '"');
        loc++;
        
        string attribValue = "";
        ch = line[loc];
        
        assert(line[loc] == '"');
        loc++;
      }
    }
  }
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

  map<string, map<string, string>> DICT;
  int _h = 0;
  for (; _h < N; _h++) {
    string line;
    getline(cin, line);
    read_hrml(line, DICT);
  }

  int _q = 0;
  for (; _q < Q; _q++) {
    string query;
    getline(cin, query);
    cout << process_query(query, DICT) << endl;
  }
  return 0;
}
