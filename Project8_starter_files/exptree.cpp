#include "exptree.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

ExpTree::ExpTree(vector<string> expr) {
    this->root = parse(expr, 0);
}

ExpTree::Node* ExpTree::parse(vector<string> &expr, int32_t position) {
    if (position < 0 || position >= expr.size()) {
        return nullptr;
    } else {
        string token = expr[position];
        expr.erase(expr.begin());
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "==" || token == "!=" || token == "<" || token == ">") {
            Node *left = parse(expr, position);
            Node *right = parse(expr, position);
            Node *n = new Node(token.c_str(), left, right);
            return n;
        }
        else if (token == "!" || token == "~")
        {
            Node *left = parse(expr, position);
            Node *n = new Node (token.c_str(), left, nullptr);
            return n;
        }
        else {
            int32_t operand = stoi(token);
            Node *n = new Node(operand);
            return n;
        }
    }
}

int32_t ExpTree::Node::eval() const {
    if (is_operand) {
        return operand;
    } else {
        int32_t left_val = (left == nullptr) ? 0 : left->eval();
        int32_t right_val = (right == nullptr) ? 0 : right->eval();
        if (optr == "+") {
            return left_val + right_val;
        } else if (optr == "-") {
            return left_val - right_val;
        } else if (optr == "*") {
            return left_val * right_val;
        } else if (optr == "/"){
            return left_val / right_val;
        } else if(optr == "<"){
            return left_val < right_val; 
        } else if(optr == ">"){
            return left_val > right_val;
        } else if(optr == "=="){
            return left_val == right_val;
        } else if(optr == "!="){
            return left_val != right_val;
        } else if (optr == "!"){
            return !left_val;
        } else if (optr == "~"){
            return -left_val;
        } else{
            abort();
        }

    }
}

int32_t ExpTree::eval() const {
    return (root == nullptr) ? 0 : root->eval();
}

string ExpTree::Node::val_as_string() const {
    return is_operand ? to_string(operand) : optr;
}

void ExpTree::printPrefix(const Node* n) const {
    if (n == nullptr) {
        return;
    }
    cout << n->val_as_string() << " ";
    printPrefix(n->left);
    printPrefix(n->right);
}

void ExpTree::printPrefix() const {
    printPrefix(root);
    cout << endl;
}

void ExpTree::printInfix(const Node *n) const {
    if (n == nullptr) {
        return;
    }
    printInfix(n->left);
    cout << n->val_as_string() << " ";
    printInfix(n->right);
}

void ExpTree::printInfix() const {
    printInfix(root);
    cout << endl;
}

