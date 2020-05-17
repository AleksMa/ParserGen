#include "ResultNode.h"

ResultNode::ResultNode(Node node, string value) : Node(node), name(value), parent(nullptr) {

}

ResultNode::ResultNode(Node node, string value, ResultNode *parent) : Node(node), name(value), parent(parent) {

}

ResultNode::ResultNode(ResultNode *resultNode) : Node(resultNode->is_terminal, resultNode->tag) {
    name = resultNode->name;
    parent = nullptr;
}
