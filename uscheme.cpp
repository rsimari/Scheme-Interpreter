// uscheme.cpp

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

using namespace std;


bool IsDigit( char c )
{
  return ( '0' <= c && c <= '9' );
}

// Globals ---------------------------------------------------------------------

bool BATCH = false;
bool DEBUG = false;

// Structures ------------------------------------------------------------------

struct Node {
    Node(string value, Node *left=nullptr, Node *right=nullptr) : value(value), left(left), right(right) {};
    ~Node() {
      delete left;
      delete right;

    };

    string value;
    Node * left;
    Node * right;

    friend ostream &operator<<(ostream &os, const Node &n);
};

ostream &operator<<(ostream &os, const Node &n) {
    return os;
}

// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token;
    return token;
}

Node *parse_expression(istream &s) {

    string currToken = parse_token(s);
    Node *left;
    Node *right;
    
    if (currToken == "" || currToken == ")") return nullptr;

    if (currToken == "(") {
      currToken = parse_token(s);
      left = parse_expression(s);
      if (left != nullptr) right = parse_expression(s);
      if (right != nullptr) parse_token(s);
    }
    return new Node(currToken, left, right);
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const Node *n, stack<int> &s) {
}

int evaluate(const Node *n) {
    return 0;
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    int c;

    while ((c = getopt(argc, argv, "bdh")) != -1) {
        switch (c) {
            case 'b': BATCH = true; break;
            case 'd': DEBUG = true; break;
            default:
                cerr << "usage: " << argv[0] << endl;
                cerr << "    -b Batch mode (disable prompt)"   << endl;
                cerr << "    -d Debug mode (display messages)" << endl;
                return 1;
        }
    }

    while (!cin.eof()) {
        if (!BATCH) {
            cout << ">>> ";
            cout.flush();
        }

        if (!getline(cin, line)) {
            break;
        }

        if (DEBUG) { cout << "LINE: " << line << endl; }

        stringstream s(line);
        Node *n = parse_expression(s);
        if (DEBUG) { cout << "TREE: " << *n << endl; }

      //  cout << evaluate(n) << endl;

        delete n;
    }

    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
