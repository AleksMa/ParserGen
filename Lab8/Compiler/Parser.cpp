#include <iostream>
#include "Parser.h"
#include "../Token/TermToken.h"
#include "../Token/NonTermToken.h"

Parser::Parser(Scanner L) : L(L) {
}

void Parser::parse() {
    Sym = L.next_token();
    Grammar();
}

Parser::~Parser() {
    for (auto t : nrules) {
        delete_node(t.second);
    }
}

void Parser::Grammar() {
    NT_DEC();
    T_DEC();
    R_LIST();
}

void Parser::NT_DEC() {
    if (Sym->get_tag() == NT_KW)
        Sym = L.next_token();
    else {
        raise_error();
        return;
    }

    NT_LIST();

    if (Sym->get_tag() == SEMICOLON)
        Sym = L.next_token();
    else {
        raise_error();
        return;
    }
}

void Parser::NT_LIST() {
    if (Sym->get_tag() == NON_TERM) {
        auto nt_term = dynamic_cast<NonTermToken *>(Sym);
        nt_to_str[nt_to_str.size()] = nt_term->ident;
        str_to_nt[nt_term->ident] = str_to_nt.size();
        declared[declared.size()] = false;
        can_eps[can_eps.size()] = false;
        Sym = L.next_token();
    } else {
        raise_error();
        return;
    }

    while (Sym->get_tag() == COMMA) {
        Sym = L.next_token();
        if (Sym->get_tag() == NON_TERM) {
            auto nt_term = dynamic_cast<NonTermToken *>(Sym);
            nt_to_str[nt_to_str.size()] = nt_term->ident;
            str_to_nt[nt_term->ident] = str_to_nt.size();
            declared[declared.size()] = false;
            can_eps[can_eps.size()] = false;
            Sym = L.next_token();
        } else {
            raise_error();
            return;
        }
    }
}

void Parser::T_DEC() {
    if (Sym->get_tag() == T_KW)
        Sym = L.next_token();
    else {
        raise_error();
        return;
    }

    T_LIST();

    if (Sym->get_tag() == SEMICOLON)
        Sym = L.next_token();
    else {
        raise_error();
        return;
    }
}

void Parser::T_LIST() {
    if (Sym->get_tag() == TERM) {
        auto t_term = dynamic_cast<TermToken *>(Sym);
        t_to_str[t_to_str.size()] = t_term->ident;
        str_to_t[t_term->ident] = str_to_t.size();
        Sym = L.next_token();
    } else {
        raise_error();
        return;
    }

    while (Sym->get_tag() == COMMA) {
        Sym = L.next_token();
        if (Sym->get_tag() == TERM) {
            auto t_term = dynamic_cast<TermToken *>(Sym);
            t_to_str[t_to_str.size()] = t_term->ident;
            str_to_t[t_term->ident] = str_to_t.size();
            Sym = L.next_token();
        } else {
            raise_error();
            return;
        }
    }
}

// R_LIST      ::= ('non_term' '::=' RIGHT_SEC ';')*;

void Parser::R_LIST() {

    int k = 0;
    while (Sym->get_tag() == NON_TERM) {
        auto nt_term = dynamic_cast<NonTermToken *>(Sym);
        if (str_to_nt.find(nt_term->ident) == str_to_nt.end()) {
            cout << "UNEXPECTED NONTERM: " << Sym << endl;
        }
        auto nt = str_to_nt[nt_term->ident];
        declared[nt] = true;

        Node *rule = new Node(true, false, true);
        nrules[nt] = rule;

        k++;

        Sym = L.next_token();

        if (Sym->get_tag() == ID_EST)
            Sym = L.next_token();
        else {
            raise_error();
            return;
        }

        RIGHT_SEC(rule);

        if (Sym->get_tag() == SEMICOLON)
            Sym = L.next_token();
        else {
            raise_error();
            return;
        }
    }
    if (k == 0) {
        cout << "NO RULES!" << endl;
        return;
    }
}

// RIGHT_SEC   ::= RIGHT_TERM ( RIGHT_TERM )* ( '|' RIGHT_SEC)*;

Node *Parser::RIGHT_SEC(Node *root) {
    Node *rule = new Node(true, false);
    root->children.push_back(rule);
    RIGHT_TERM(rule);
    while (Sym->get_tag() == NON_TERM
           || Sym->get_tag() == TERM
           || Sym->get_tag() == EPSILON
           || Sym->get_tag() == L_PAR) {
        RIGHT_TERM(rule);
    }
    while (Sym->get_tag() == OR) {
        Sym = L.next_token();
        RIGHT_SEC(root);
    }
    return rule;
}

// RIGHT_TERM  ::= 'non_term' | 'term' | 'epsilon' | '(' RIGHT_SEC ')' ('*')?;

void Parser::RIGHT_TERM(Node *root) {
    if (Sym->get_tag() == NON_TERM) {
        auto nt_cur_token = dynamic_cast<NonTermToken *>(Sym);
        auto nt_cur = str_to_nt[nt_cur_token->ident];
        root->children.push_back(new Node(false, nt_cur));
        Sym = L.next_token();
    } else if (Sym->get_tag() == TERM) {
        auto t_cur_token = dynamic_cast<TermToken *>(Sym);
        auto t_cur = str_to_t[t_cur_token->ident];
        root->children.push_back(new Node(true, t_cur));
        Sym = L.next_token();
    } else if (Sym->get_tag() == EPSILON) {
        root->children.push_back(new Node(true, EPSILON));
        Sym = L.next_token();
    } else if (Sym->get_tag() == L_PAR) {
        Sym = L.next_token();
        Node *rule = new Node(true, false, true);
        root->children.push_back(rule);
        RIGHT_SEC(rule);
        if (Sym->get_tag() == R_PAR) {
            Sym = L.next_token();
        } else {
            raise_error();
            return;
        }
        if (Sym->get_tag() == STAR) {
            rule->is_repeat = true;
            Sym = L.next_token();
        }
    } else {
        raise_error();
        return;
    }
}

void Parser::raise_error() {
    cout << "ERR: " << Sym->to_str() << endl;
}

void Parser::delete_node(Node *node) {
    for (auto & i : node->children) {
        delete_node(i);
    }
    delete node;
}

void Parser::create_first() {
    bool change = false;
    do {
        change = false;
        for (int i = 0; i < nt_to_str.size(); ++i) {
            auto nt_rules = nrules[i]->children;
            set<int> all;
            for (int j = 0; j < nt_rules.size(); ++j) {
                auto s = find_first(nt_rules[j]);
                all.insert(s.begin(), s.end());
            }
            if (all.size() != first[i].size())
                change = true;
            first[i].insert(all.begin(), all.end());
        }
    } while (change);

    cout << "FIRST:" << endl;
    for (int i = 0; i < nt_to_str.size(); ++i) {
        cout << nt_to_str[i] << ": ";
        for (auto f : first[i]) {
            cout << t_to_str[f] << ", ";
        }
        cout << endl;
    }

}

set<int> Parser::find_first(Node *node) {
    if (!node->is_internal) {
        if (node->is_terminal) {
            return {node->tag};
        } else {
            return first[node->tag];
        }
    } else {
        set<int> s;
        if (node->is_or) {
            for (auto & i : node->children) {
                auto found = find_first(i);
                s.insert(found.begin(), found.end());
            }
        } else {
            for (auto & i : node->children) {
                auto found = find_first(i);
                s.insert(found.begin(), found.end());
                if (!i->is_repeat)
                    break;
            }
        }
        return s;
    }
}


