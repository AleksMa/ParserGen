#ifndef LAB71_COMPILER_H
#define LAB71_COMPILER_H

#include "Scanner.h"
#include "Parser.h"
#include <vector>
#include <map>
#include "../Utils/Token/Token.h"
#include "../Utils/Message/Message.h"

using namespace std;

typedef map<pair<int, int>, vector<pair<bool, int>>> MPVP;

class Compiler {
private:
    vector<pair<Position, Message>> messages;

    vector<string> names;
    map<string, int> name_codes;

    map<int, string> nt_to_str;
    map<string, int> str_to_nt;

    map<int, string> t_to_str;
    map<string, int> str_to_t;

    map<int, bool> can_eps;
    map<int, bool> declared;

    map<int, set<int>> first;
    map<int, set<int>> follow;

    map<int, vector<vector<pair<bool, int>>>> rules;

    int axiom;

    bool error = false;
    string error_msg;

public:
    Compiler();
    ~Compiler();

    int add_name(string name);
    string get_name(int code);

    void add_message(bool is_error, Position c, string text);
    void output_messages();

    Scanner get_scanner(string program);
    Parser get_parser(Scanner lex);

    bool has_error() { return error; };
    string get_error() { return error_msg; };
};

#endif //LAB71_COMPILER_H
