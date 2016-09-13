// uscheme.cpp

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>
#include <memory>
#include <cctype>

using namespace std;

// Globals ---------------------------------------------------------------------

bool BATCH = false;
bool DEBUG = false;

// Structures ------------------------------------------------------------------

struct Node {
    Node(string value, shared_ptr<Node> left=nullptr, shared_ptr<Node> right=nullptr) : value(value), left(left), right(right) {}
    ~Node() {};

    string value;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    friend ostream &operator<<(ostream &os, const Node &n);
};

bool isOperator(string token) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      return true;
    }
    return false;
}

void printPreOrder(const shared_ptr<Node> root) {
  if (root == nullptr) return;

  cout << "(Node: value="<< root->value;
  if (root->left) cout << ", left=";
  printPreOrder(root->left);
  if (root->right) cout <<", right=";
  printPreOrder(root->right);
  cout << ")";


}

ostream &operator<<(ostream &os, const Node &n) {
    auto root = make_shared<Node>(n);
    printPreOrder(root);
    return os;
}




// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token;
    char next;
    s >> next;
    if ((next == '(' || next == ')') || isOperator(string(1, next))) {
        token = next;
    } else if (isdigit(next)) {
        token = next;
        while (isdigit(s.peek())) {
            token += s.get();
        }
    }
    return token;
}

shared_ptr<Node> parse_expression(istream &s) {
    string currToken = parse_token(s);
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;
    if (currToken == "" || currToken == ")") return nullptr;

    if (currToken == "(") {
      currToken = parse_token(s);
      left = parse_expression(s);
      if (left != nullptr) right = parse_expression(s);
      if (right != nullptr) parse_token(s);
    }
    return shared_ptr<Node> (new Node(currToken, left, right));
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const shared_ptr<Node> n, stack<int> &s) {
    // a and b are on the top of the stack and need to be operated on
    int b = s.top(); s.pop();
    int a = s.top(); s.pop();
    if (n->value == "+") {
        s.push(a + b);
    } else if (n->value == "-") {
        s.push(a - b);
    } else if (n->value == "*") {
        s.push(a * b);
    } else if (n->value == "/") {
        s.push(a / b);
    } 
}

void postOrderBuild(const shared_ptr<Node> root, stack <int> &s) {
  if (root == nullptr) return;

  postOrderBuild(root->left, s);
  postOrderBuild(root->right, s);

  if (isOperator(root->value)) {
    evaluate_r(root, s);
  }
  else {
    s.push(stoi(root->value));
  }
}

int evaluate(const shared_ptr<Node> n) {
    stack<int> s;
    postOrderBuild(n, s);
    return s.top();
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
        shared_ptr<Node> n = parse_expression(s);
        if (DEBUG) { cout << "TREE: " << *n << endl; }

        cout << evaluate(n) << endl;
    }

    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
