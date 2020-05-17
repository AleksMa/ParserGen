#include <iostream>
#include "Compiler.h"
#include "Scanner.h"
#include "../../Utils/Node/TokenNode.h"

using namespace std;

Compiler::Compiler() = default;

int Compiler::add_name(string name) {
    if (name_codes.find(name) == name_codes.end()) {
        int code = name_codes.size();
        name_codes[name] = code;
        return code;
    }
    return name_codes[name];
}

string Compiler::get_name(int code) {
    return names[code];
}

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
        if (old_node->tag == COMMA || old_node->tag == NT_KW || old_node->tag == T_KW
            || old_node->tag == SEMICOLON || old_node->tag == END_OF_PROGRAM
            || old_node->tag == AXIOM || old_node->tag == OR || old_node->tag == ID_EST)
            return;

        TokenNode *tn = dynamic_cast<TokenNode *>(old_node);
        TokenNode *astnode = new TokenNode(old_node, tn->value);
        astnode->parent = root;
        root->children.push_back(astnode);
        return;
    }

    if (old_node->tag == RULE_TAIL || old_node->tag == RIGHT_SUB || old_node->tag == NT_TAIL
        || old_node->tag == T_TAIL || old_node->tag == NT_LIST || old_node->tag == T_LIST
        || old_node->tag == RIGHT_TAIL) {
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

void Compiler::analize_rule(ResultNode *node) {
    ResultNode *NT = node->children[0];

    TokenNode *tn = dynamic_cast<TokenNode *>(NT);
    string nontermstr = tn->value;
    int nt_i = str_to_nt[nontermstr];

    for (int i = 1; i < node->children.size(); ++i) {
        vector<pair<bool, int>> rule;
        vector<ResultNode *> right = node->children[i]->children;
        for (int j = 0; j < right.size(); ++j) {
            auto cur_node = right[j];

            TokenNode *first_tn = dynamic_cast<TokenNode *>(cur_node);
            string tokenstr = first_tn->value;

            if (cur_node->tag == TERM) {
                int t_i = str_to_t[tokenstr];
                rule.push_back({1, t_i});
            } else if (cur_node->tag == NON_TERM) {
                int nnt_i = str_to_nt[tokenstr];
                rule.push_back({0, nnt_i});
            }
        }
        rules[nt_i].push_back(rule);
    }
}


void Compiler::analize_nonterms(ResultNode *node) {

    for (int i = 0; i < node->children.size(); ++i) {
        auto child_node = node->children[i];

        TokenNode *nt_node = dynamic_cast<TokenNode *>(child_node);
        string nontermstr = nt_node->value;
        str_to_nt[nontermstr] = str_to_nt.size();
        nt_to_str[str_to_nt.size() - 1] = nontermstr;

        int nt_i = str_to_nt[nontermstr];
        first[nt_i] = {};
        follow[nt_i] = {};
        rules[nt_i] = {};
        can_eps[nt_i] = false;
    }
}

void Compiler::analize_terms(ResultNode *node) {

    for (int i = 0; i < node->children.size(); ++i) {
        auto child_node = node->children[i];

        TokenNode *t_node = dynamic_cast<TokenNode *>(child_node);
        string termstr = t_node->value;
        str_to_t[termstr] = str_to_t.size();
        t_to_str[str_to_nt.size() - 1] = termstr;

        int t_i = str_to_t[termstr];
    }
}


void Compiler::search_for_tag(ResultNode *node, int tag, ResultNode **searched) {
    if (node->is_terminal)
        return;

    if (node->tag == tag) {
        *searched = node;
        return;
    }

    for (auto &i : node->children) {
        search_for_tag(i, tag, searched);
    }
}

void Compiler::create_grammar(ResultNode *root) {
    ResultNode *node;
    search_for_tag(root, NT_DEC, &node);
    analize_nonterms(node);

    search_for_tag(root, T_DEC, &node);
    analize_terms(node);

    search_for_tag(root, R_LIST, &node);
    //print_node(node, 0);
    for (auto &i : node->children) {
        analize_rule(i);
    }

    bool fixed_first = true;
    bool fixed_follow = true;
    while (fixed_first || fixed_follow) {
        fixed_first = false;
        fixed_follow = false;

        for (auto mit = rules.begin(); mit != rules.end(); mit++) {
            int i = (*mit).first;
            vector<vector<pair<bool, int>>> nt_rules = rules[i];
            for (int j = 0; j < nt_rules.size(); ++j) {
                vector<pair<bool, int>> nt_rule = nt_rules[j];
                if (nt_rule.size() > 0) {
                    int t_0 = nt_rule[0].second;
                    if (nt_rule[0].first) {
                        if (first[i].find(t_0) == first[i].end()) {
                            first[i].insert(t_0);
                            fixed_first = true;
                        }
                    } else {
                        set<int> nnt_first = first[t_0];
                        for (auto it = nnt_first.begin(); it != nnt_first.end(); it++) {
                            if (first[i].find(*it) == first[i].end()) {
                                fixed_first = true;
                                first[i].insert(*it);
                            }
                        }
                    }

                    for (int k = 0; k < nt_rule.size(); ++k) {
                        pair<bool, int> t_k = nt_rule[k];
                        if (!t_k.first) {
                            if (k < nt_rule.size() - 1) {
                                if (nt_rule[k + 1].first) {
                                    auto t_next = nt_rule[k + 1];
                                    if (follow[t_k.second].find(t_next.second) == follow[t_k.second].end()) {
                                        follow[t_k.second].insert(t_next.second);
                                        fixed_follow = true;
                                    }
                                } else {
                                    set<int> nnt_first = first[nt_rule[k + 1].second];
                                    for (auto it = nnt_first.begin(); it != nnt_first.end(); it++) {
                                        if (follow[t_k.second].find(*it) == follow[t_k.second].end()) {
                                            fixed_follow = true;
                                            follow[t_k.second].insert(*it);
                                        }
                                    }
                                }
                            }
                            if (k == nt_rule.size() - 1) {
                                set<int> nnt_first = follow[i];
                                for (auto it = nnt_first.begin(); it != nnt_first.end(); it++) {
                                    if (follow[t_k.second].find(*it) == follow[t_k.second].end()) {
                                        fixed_follow = true;
                                        follow[t_k.second].insert(*it);
                                    }
                                }
                            }
                            if (k == nt_rule.size() - 2 && !nt_rule[k + 1].first && can_eps[nt_rule[k + 1].second]) {
                                set<int> nnt_first = follow[i];
                                for (auto it = nnt_first.begin(); it != nnt_first.end(); it++) {
                                    if (follow[t_k.second].find(*it) == follow[t_k.second].end()) {
                                        fixed_follow = true;
                                        follow[t_k.second].insert(*it);
                                    }
                                }
                            }
                        }
                    }
                } else {
                    can_eps[i] = true;
                }
            }
        }
    }

    // pair<rule, domain_tag>
    map<pair<int, int>, vector<pair<bool, int>>> new_D;

    for (auto mit = rules.begin(); mit != rules.end(); mit++) {
        int i = (*mit).first;
        vector<vector<pair<bool, int>>> nt_rules = rules[i];
        for (int j = 0; j < nt_rules.size(); ++j) {
            vector<pair<bool, int>> nt_rule = nt_rules[j];
            if (nt_rule.size() > 0) {
                int t_0 = nt_rule[0].second;
                if (nt_rule[0].first) {
                    new_D[{i, t_0}] = nt_rule;
                } else {
                    auto t_0_first = first[t_0];
                    for (auto it = t_0_first.begin(); it != t_0_first.end(); it++) {
                        new_D[{i, *it}] = nt_rule;
                    }
                }
            } else {
                auto i_follow = follow[i];
                for (auto it = i_follow.begin(); it != i_follow.end(); it++) {
                    new_D[{i, *it}] = nt_rule;
                }
            }
        }
    }

    auto rnames = calc_rule_names;
    auto tnames = calc_token_names;

    cout << "{";
    for (auto mit = new_D.begin(); mit != new_D.end(); mit++) {
        auto pbi = (*mit).first;
        auto nt_rule = (*mit).second;
        cout << "{";

        cout << "{" << rnames[pbi.first] << ", " << tnames[pbi.second] << "}, {";

        for (int i = 0; i < nt_rule.size(); ++i) {
            auto lpbi = nt_rule[i];
            cout << "{" << lpbi.first << ", " << (lpbi.first ? tnames[lpbi.second] : rnames[lpbi.second]) << "}, ";
        }

        cout << "}}," << endl;
    }
    cout << "}" << endl;



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

Compiler::Compiler(bool calc): calculator(calc) {}

