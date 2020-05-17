#ifndef LAB71_RESULTNODE_H
#define LAB71_RESULTNODE_H


#include <string>
#include <vector>
#include "Node.h"

using namespace std;

class ResultNode : public Node {
public:
    string name;

    ResultNode *parent;
    vector<ResultNode*> children;

    virtual string get_value() { return name; };

    ResultNode(Node node, string value);
    ResultNode(Node node, string value, ResultNode *parent);
    ResultNode(ResultNode *resultNode);
};


#endif //LAB71_RESULTNODE_H
