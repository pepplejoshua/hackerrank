#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>

using namespace std;
struct Tag {
  string identifier;
  map<string, string> attribs;
  map<string, Tag*> children;
};

map<string, Tag*> parse_hrml(vector<string> lines) {
  vector<Tag*> stack;
  Tag *root = NULL;
  map<string, Tag*> top_tags;

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

      if (c == ' ') {
        i++;
        c = line[i];
      }

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
        top_tags[tag] = node;
        root = node;
      } else {
        // it is nested inside another node
        Tag *last = stack.back();
        last->children[tag] = node;
      }
      stack.push_back(node);
    }

  }
  return top_tags;
}

string query_hrml(map<string, Tag*> root, string q) {
  Tag *cur;
  size_t tilde = q.find('~');
  int i = 0;

  // read first tag to match root
  size_t first_dot = q.find('.');
  if (first_dot != string::npos) {
    string first_tag = q.substr(0, first_dot);
    if (root.find(first_tag) != root.end()) {
      cur = root[first_tag];
    } else {
      return "Not Found!";
    }

    i = first_dot + 1; // start matching past the first tag
    while (i < tilde) {
      string tag = "";
      char c = q[i];
      while(c != '.' && c != '~') {
        tag += c;
        i++;
        c = q[i];
      }

      if (c == '.') {
        i++;
        c = q[i];
      }

      if (cur->identifier == tag) break;
      if (cur->children.find(tag) == cur->children.end()) {
        return "Not Found!";
      }
      cur = cur->children[tag];
    }
  } else {
    string first_tag = q.substr(0, tilde);
    // cout << "SHORT HRML: " << first_tag << endl;
    if (root.find(first_tag) != root.end()) {
      // cout << "SHORT HRML: " << cur->identifier << endl;
      cur = root[first_tag];
    } else {
      return "Not Found!";
    }
    i = tilde; // start matching past the first tag
  }

  assert(q[i] == '~');
  i++;
  string attrib = q.substr(i, q.size());
  // cout << "SHORT HRML search: " << attrib << endl;
  if (cur->attribs.find(attrib) != cur->attribs.end()) {
    return cur->attribs[attrib];
  } else {
    return "Not Found!";
  }
}

int main() {
  // N is the number of lines of HRML program
  // Q is the number of queries that follow this program
  int N, Q;
  cin >> N >> Q;
  // skip newline character from the N Q line
  cin.ignore(1);

  int _h = 0;
  vector<string> hrml;
  for (; _h < N; _h++) {
    string line;
    getline(cin, line);
    hrml.push_back(line);
  }
  map<string, Tag*> root = parse_hrml(hrml);

  int _q = 0;
  for (; _q < Q; _q++) {
    string query;
    getline(cin, query);
    cout << query_hrml(root, query) << endl;
  }

  return 0;
}
