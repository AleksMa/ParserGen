#include "Node.h"

Node::Node(bool is_terminal, int tag) : is_terminal(is_terminal), tag(tag) {}

Node::Node(int tag) : tag(tag), is_terminal(true) {}

Node::Node(bool is_internal, bool is_repeat, bool is_or): is_repeat(is_repeat), is_internal(is_internal), is_or(is_or) {}

Node::Node(bool is_internal, bool is_repeat): is_repeat(is_repeat), is_internal(is_internal) {}
