#include <iostream>
#include "Compiler.h"
#include "Scanner.h"
#include "../../Utils/Node/TokenNode.h"

using namespace std;

Compiler::Compiler() = default;

void Compiler::add_message(bool is_error, Position c, string text) {
    messages.emplace_back(c, Message(is_error, text));
}

void Compiler::output_messages() {
    for (auto message : messages) {
        cout << (message.second.get_error() ? "E" : "W");
        cout << " " << message.first.to_str();
        cout << ": " << message.second.get_text() << endl;
    }
}

Scanner Compiler::get_scanner(string program) {
    return Scanner(program, this);
}

Parser Compiler::get_parser(Scanner lex, MPVP D) {
    return Parser(lex, D);
}


ResultNode *Compiler::makeAST(ResultNode *root) {
    astroot = new ResultNode(root);

    for (auto &child : root->children) {
        nodeAST(astroot, child);
    }

    return astroot;
}

void Compiler::nodeAST(ResultNode *root, ResultNode *old_node) {
    if (old_node->is_terminal) {
        if (old_node->tag == SUM || old_node->tag == MUL || old_node->tag == LPAR || old_node->tag == RPAR)
            return;

        TokenNode *tn = dynamic_cast<TokenNode *>(old_node);
        TokenNode *astnode = new TokenNode(old_node, tn->value);
        astnode->parent = root;
        root->children.push_back(astnode);
        return;
    }

    if (old_node->tag == T1 || old_node->tag == E1 || old_node->tag == F
    || ((old_node->tag == E || old_node->tag == T) && old_node->children.size() <= 1 )) {
        for (auto &child : old_node->children) {
            nodeAST(root, child);
        }
        return;
    }

    ResultNode *astnode = new ResultNode(old_node);
    astnode->parent = root;
    root->children.push_back(astnode);
    for (auto &child : old_node->children) {
        nodeAST(astnode, child);
    }
}


void Compiler::print_tree(ResultNode *root) {
    print_node(root->children[0], 0);
    cout << endl << endl;
}

void Compiler::print_node(ResultNode *node, int level) {
    string prefix;
    for (int i = 0; i < level; ++i) {
        prefix += "  ";
    }
    cout << prefix << "> " << node->name << endl;
    for (auto &i : node->children) {
        print_node(i, level + 1);
    }
}

int Compiler::calculate(ResultNode *root) {

    if (root->tag == N) {
        return stoi(root->get_value());
    }

    int res;
    if (root->tag == T) {
        res = 1;
        for (auto &i : root->children) {
            res *= calculate(i);
        }
    } else {
        res = 0;
        for (auto &i : root->children) {
            res += calculate(i);
        }
    }
    return res;
}

Compiler::~Compiler() {
    delete_node(astroot);
}

void Compiler::delete_node(ResultNode *node) {
    for (auto &i : node->children) {
        delete_node(i);
    }
    delete node;
}

