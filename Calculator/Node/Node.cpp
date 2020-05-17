#include "Node.h"

Node::Node(bool is_terminal, int tag) : is_terminal(is_terminal), tag(tag) {}

Node::Node(int tag) : tag(tag), is_terminal(true) {

}
