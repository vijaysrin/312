#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class ExpTree {

    class Node {
    public:

        bool is_operand;
        int operand;
        string optr;

        Node *left;
        Node *right;

        Node(int operand) {
            this->is_operand = true;
            this->operand = operand;
            this->optr = "0";
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(string optr, Node* left, Node *right) {
            this->is_operand = false;
            this->operand = 0;
            this->optr = optr;
            this->left = left;
            this->right = right;
        }

        string val_as_string() const;
        int32_t eval() const;
    };

    // root of the expression tree
    Node *root;

    static Node* parse(vector<string> &expr, int32_t position);
    void printInfix(const Node *n) const;
    void printPrefix(const Node *n) const;

public:

    ExpTree(vector<string> expr);

    void printInfix() const;
    void printPrefix() const;
    int32_t eval() const;
};
