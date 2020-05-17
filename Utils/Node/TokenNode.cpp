//
// Created by a.mamaev on 10.05.2020.
//

#include "TokenNode.h"


TokenNode::TokenNode(ResultNode *rn, string value) : ResultNode(*rn), value(value) {

}

TokenNode::TokenNode(ResultNode rn, string value) : ResultNode(rn), value(value) {

}
