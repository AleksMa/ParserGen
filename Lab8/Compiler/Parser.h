#ifndef LAB71_PARSER_H
#define LAB71_PARSER_H


#include <vector>
#include <map>
#include <stack>
#include "../Utils/Token/Token.h"
#include "../Utils/Node/Node.h"
#include "../Utils/NameMap.h"
#include "Scanner.h"

using namespace std;

typedef map<pair<int, int>, vector<pair<bool, int>>> MPVP;

class Compiler;

class Parser {
private:
    Compiler *compiler;

    Token *Sym;

    map<int, string> nt_to_str;
    map<string, int> str_to_nt;

    map<int, string> t_to_str;
    map<string, int> str_to_t;

    map<int, bool> can_eps;
    map<int, bool> declared;

    map<int, set<int>> first;

    map<int, Node*> nrules;

    map<int, vector<vector<pair<bool, int>>>> rules;

    Scanner L;

    Node *rootest = nullptr;

    void raise_error();

    void delete_node(Node *node);

public:
    Parser(Scanner L);

    ~Parser();


    // non-terminal    GRAMMAR, NT_DEC, NT_LIST, T_DEC, T_LIST, R_LIST, RIGHT_SEC, RIGHT_TERM;

    void Grammar();

    void NT_DEC();

    void NT_LIST();

    void T_DEC();

    void T_LIST();

    void R_LIST();

    Node *RIGHT_SEC(Node *root);

    void RIGHT_TERM(Node *root);

    void parse();

    void create_first();
    set<int> find_first(Node *node);
};


#endif //LAB71_PARSER_H
