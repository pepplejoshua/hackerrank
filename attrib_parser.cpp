#include <cmath>
#include <cstdio>
#include <map>
#include <queue>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

struct HRML {
  string tag;
  map<string, string> attributes;
  map<string, size_t> sub_tags;
};

// used to track all the hrml tags as we read them
// we will pop one whenever we see its closing tag and store it inside
// the item before it, unless it is the last item, in which case, we do
// nothing. the last item will be used as the starting point for queries.
// it is essentially a linked list, where there can be multiple links from a
// node
HRML STACK[20];
int STACK_IN = 0;

void read_hrml(string line) {
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

    // make sure the closing tag we just read matches the 
    // tag of the last item in the stack
    HRML latest_hrml = STACK[STACK_IN];
    assert(latest_hrml.tag == tag);
    STACK_IN--;
    HRML cur_hrml = STACK[STACK_IN];
    cur_hrml.sub_tags[tag] = STACK_IN+1;
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
      HRML node = STACK[STACK_IN];
      node.tag = tag;
      assert(STACK_IN < 20);
      STACK[STACK_IN] = node;
      STACK_IN++;
      loc++; // go to newline
      assert(line.size() == loc);
    } else {
      // there are attributes to read:
      // attribName = "value">
      // attribName2="value" ..>
      loc++; // go to start of attribute name
      map<string, string> attrib_dict;

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
        while (ch != '"') {
          attribValue += ch;
          loc++;
          ch = line[loc];
        }
        
        assert(line[loc] == '"');
        loc++;

        attrib_dict[attribName] = attribValue;
        cout << attribName << " => " << attribValue << endl;

        ch = line[loc];
        if (ch == ' ') {
          loc++;
          ch = line[loc];
        }
      }

      assert(ch == '>');
      HRML node = STACK[STACK_IN];
      node.tag = tag;
      node.attributes = attrib_dict;
      assert(STACK_IN < 20);
      STACK[STACK_IN] = node;
      STACK_IN++;
      loc++;
      assert(line.size() == loc);
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

  int _h = 0;
  for (; _h < N; _h++) {
    string line;
    getline(cin, line);
    read_hrml(line);
  }

  int _q = 0;
  for (; _q < Q; _q++) {
    string query;
    getline(cin, query);
    // cout << process_query(query, DICT) << endl;
  }

  return 0;
}
