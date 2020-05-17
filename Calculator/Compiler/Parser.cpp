#include <iostream>
#include "Parser.h"
#include "../Node/TokenNode.h"
#include "../Token/TermToken.h"
#include "../Token/NonTermToken.h"

Parser::Parser(Scanner L, MPVP D) : L(L), D(D) {
}

void Parser::parse() {
    root = new ResultNode(Node(false, 0), "");

    S.push(new ResultNode(GRAMMAR_NODE, rule_names[GRAMMAR], root));

    Token *token = L.next_token();
    do {
        ResultNode *top = S.top();

        if (top->is_terminal) {
            if (top->tag == token->get_tag()) {
                TokenNode *tn = dynamic_cast<TokenNode*>(top);
                tn->parent->children.push_back(top);
                tn->name = token->to_str();
                if (token->get_tag() == TERM) {
                    TermToken *tt = dynamic_cast<TermToken*>(token);
                    string term_str = tt->ident.substr(1, tt->ident.size() - 2);
                    tn->value = term_str;;
                }
                if (token->get_tag() == NON_TERM) {
                    NonTermToken *tt = dynamic_cast<NonTermToken*>(token);
                    tn->value = tt->ident;
                }
                S.pop();
                token = L.next_token();
            } else {
                cout << "Unexpected token: " << token->to_str() << endl;
                return;
            }
        } else if (D.find({static_cast<rule>(top->tag), token->get_tag()}) != D.end()) {
            rule r = static_cast<rule>(top->tag);
            vector<pair<bool, int>> right = D[{r, token->get_tag()}];
            if (right.size() == 0) {
                S.pop();
            } else {
                S.top()->parent->children.push_back(top);
                S.pop();
                for (int i = right.size() - 1; i >= 0; --i) {
                    Node child = Node(right[i].first, right[i].second);
                    if (child.is_terminal) {
                        ResultNode trn(child, "", top);
                        S.push(new TokenNode(trn, ""));
                    }
                    else
                        S.push(new ResultNode(child, rule_names[static_cast<rule>(child.tag)], top));
                }
            }
        } else {
            cout << "Unexpected: " << token->to_str() << endl;
            return;
        }
    } while (!S.empty());
}

void Parser::print_result() {
    for (auto &i : result) {
        cout << rule_names[i.first] << " => ";
        for (auto e : i.second) {
            cout << get_name(e) << ", ";
        }
        cout << endl;
    }
}

string Parser::get_name(Node node) {
    return node.is_terminal ? to_string(node.tag) : rule_names[static_cast<rule>(node.tag)];
}


void Parser::print_tree() {
    print_node(root->children[0], 0);
}

void Parser::print_node(ResultNode *node, int level) {
    string prefix;
    for (int i = 0; i < level; ++i) {
        prefix += "  ";
    }
    cout << prefix << "> " << node->name << endl;
    for (auto &i : node->children) {
        print_node(i, level + 1);
    }
}

Parser::~Parser() {
    delete_node(root);
}

void Parser::delete_node(ResultNode *node) {
    for (auto &i : node->children) {
        delete_node(i);
    }
    delete node;
}

ResultNode *Parser::get_root() const {
    return root;
}


