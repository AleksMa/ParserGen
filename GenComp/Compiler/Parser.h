#ifndef LAB71_PARSER_H
#define LAB71_PARSER_H


#include <vector>
#include <map>
#include <stack>
#include "../../Utils/Token/Token.h"
#include "../../Utils/Node/Node.h"
#include "../../Utils/Node/ResultNode.h"
#include "../../Utils/NameMap.h"
#include "Scanner.h"

using namespace std;

typedef map<pair<int, int>, vector<pair<bool, int>>> MPVP;

class Compiler;

class Parser {
private:
    Compiler *compiler;

    MPVP D;

    stack<ResultNode*> S;
    vector<pair<rule, vector<Node>>> result;

    Scanner L;

    ResultNode *root = nullptr;

    Node GRAMMAR_NODE = Node(false, GRAMMAR);

    void print_node(ResultNode *node, int level);
    void delete_node(ResultNode *node);

    string get_name(Node node);

public:
    Parser(Scanner L, MPVP D);
    ~Parser();

    void parse();
    void print_tree();

    ResultNode *get_root() const;
};


#endif //LAB71_PARSER_H
