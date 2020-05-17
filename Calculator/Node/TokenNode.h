//
// Created by a.mamaev on 10.05.2020.
//

#ifndef LAB71_TOKENNODE_H
#define LAB71_TOKENNODE_H


#include "ResultNode.h"

class TokenNode: public ResultNode {
public:
    string value;
    TokenNode(ResultNode *rn, string value);
    TokenNode(ResultNode rn, string value);

    string get_value() override { return value; };
};


#endif //LAB71_TOKENNODE_H
