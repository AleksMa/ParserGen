#ifndef LAB71_NODE_H
#define LAB71_NODE_H


class Node {
public:
    bool is_terminal;
    int tag;

    Node(bool is_terminal, int tag);
    Node(int tag);
};


#endif //LAB71_NODE_H
