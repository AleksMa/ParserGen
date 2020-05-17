#ifndef LAB71_COMPILER_H
#define LAB71_COMPILER_H

#include "Scanner.h"
#include "Parser.h"
#include <vector>
#include <map>
#include "../../Utils/Token/Token.h"
#include "../../Utils/Message/Message.h"

using namespace std;

typedef map<pair<rule, domain_tag>, vector<pair<bool, int>>> MPVP;

class Compiler {
private:
    vector<pair<Position, Message>> messages;

    vector<string> names;
    map<string, int> name_codes;

    ResultNode *astroot;

    void analize_rule(ResultNode *node);
    void search_for_tag(ResultNode *node, int tag, ResultNode **searched);

    map<int, string> nt_to_str;
    map<string, int> str_to_nt;

    map<int, string> t_to_str;
    map<string, int> str_to_t;

    map<int, bool> can_eps;

    map<int, set<int>> first;
    map<int, set<int>> follow;

    map<int, vector<vector<pair<bool, int>>>> rules;

    bool calculator = false;

public:
    Compiler();
    Compiler(bool calc);
    ~Compiler();

    int add_name(string name);
    string get_name(int code);

    void add_message(bool is_error, Position c, string text);
    void output_messages();

    Scanner get_scanner(string program);
    Parser get_parser(Scanner lex, MPVP D);

    ResultNode *makeAST(ResultNode *root);

    void nodeAST(ResultNode *root, ResultNode *old_node);

    void print_tree(ResultNode *root);

    void print_node(ResultNode *node, int level);

    void create_grammar(ResultNode *root);

    void delete_node(ResultNode *node);

    void analize_nonterms(ResultNode *node);

    void analize_terms(ResultNode *node);
};

#endif //LAB71_COMPILER_H
