#ifndef LAB71_COMPILER_H
#define LAB71_COMPILER_H

#include "Scanner.h"
#include "Parser.h"
#include <vector>
#include <map>
#include "../../Utils/Token/Token.h"
#include "../../Utils/Message/Message.h"

using namespace std;

class Compiler {
private:
    vector<pair<Position, Message>> messages;

    ResultNode *astroot;;

public:
    Compiler();
    Compiler(bool calc);
    ~Compiler();

    void add_message(bool is_error, Position c, string text);
    void output_messages();

    Scanner get_scanner(string program);
    Parser get_parser(Scanner lex, MPVP D);

    ResultNode *makeAST(ResultNode *root);

    void nodeAST(ResultNode *root, ResultNode *old_node);

    void print_tree(ResultNode *root);

    void print_node(ResultNode *node, int level);

    int calculate(ResultNode *root);

    void delete_node(ResultNode *node);
};

#endif //LAB71_COMPILER_H
