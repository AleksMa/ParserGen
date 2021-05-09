#ifndef LAB71_NODE_H
#define LAB71_NODE_H


#include <vector>

class Node {
public:
    bool is_terminal;
    int tag = -2;

    bool is_internal = false;
    bool is_repeat = false;
    bool is_or = false;
    std::vector<Node *> children;

    Node(bool is_terminal, int tag);
    Node(bool is_internal, bool is_repeat, bool is_or);
    Node(bool is_internal, bool is_repeat);
    Node(int tag);
};


#endif //LAB71_NODE_H
