#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>

struct Tag {
  string identifier;
  map<string, string> attribs;
  map<string, Tag*> children;
};

using namespace std;

Tag* parse_hrml(vector<string> lines) {
  vector<Tag*> stack;
  Tag *root = NULL;

  for (auto line : lines) {
    int i = 0;
    assert(line[i] == '<');
    i++;

    if (line[i] == '/') {
      // this is a closing tag.
      // read the tag's label
      i++;
      string tag = "";
      char c = line[i];
      while (c != '>') {
        tag += c;
        i++;
        c = line[i];
      }
      i++; // go to \n
      assert(line.size() == i);

      // ensure there is something to close
      // and that the current tag matches the tag of the last thing
      // on the stack, then we can pop that last item
      assert(!stack.empty());
      Tag *last = stack.back();
      assert(last->identifier == tag);
      stack.pop_back();
    } else {
      // this is an opening tag
      char c = line[i];
      string tag = "";
      while (c != '>' && c != ' ') {
        tag += c;
        i++;
        c = line[i];
      }

      Tag *node = new Tag {
        .identifier = tag,
      };

      while (c != '>') {
        string attrib_name = "";
        c = line[i];
        while (c != '=' && c != ' ') {
          attrib_name += c;
          i++;
          c = line[i];
        }

        if (c == ' ') {
          i++;
          c = line[i];
        }

        assert(c == '=');
        i++;
        c = line[i];
        if (c == ' ') {
          i++;
          c = line[i];
        }
        
        assert(c == '"');
        i++;
        c = line[i];

        string attrib_val = "";
        while (c != '"') {
          attrib_val += c;
          i++;
          c = line[i];
        }

        assert(c == '"');
        i++;
        c = line[i];

        node->attribs[attrib_name] = attrib_val;

        if (c == ' ') {
          // there are more attributes to read, so skip this character
          i++;
          c = line[i];
        }
      }

      if (stack.empty()) {
        // this is the root node
        root = node;
      } else {
        // it is nested inside another node
        Tag *last = stack.back();
        last->children[tag] = node;
      }
      stack.push_back(node);
    }

    return root;
  }
}

string query_hrml(Tag* root, string query) {

}

int main() {
  // N is the number of lines of HRML program
  // Q is the number of queries that follow this program
  int N, Q;
  cin >> N >> Q;
  // skip newline character from the N Q line
  cin.ignore(1);

  

  return 0;
}
