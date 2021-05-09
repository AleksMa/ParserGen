//
// Created by a.mamaev on 06.06.2020.
//

#ifndef GENCOMP72_INTERNALNODE_H
#define GENCOMP72_INTERNALNODE_H


#include "Node.h"
#include <vector>

using namespace std;

class InternalNode : public Node {
public:
    bool repeat;
    vector<InternalNode *> children;
};


#endif //GENCOMP72_INTERNALNODE_H
