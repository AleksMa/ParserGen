#ifndef LAB71_SCANNER_H
#define LAB71_SCANNER_H

#include <string>
#include <set>
#include "../Utils/Token/Token.h"


using namespace std;

class Compiler;

class Scanner {
private:
    string program;
    Position cur;
    Compiler *compiler;

    long parse_val();

public:
    Scanner(string source, Compiler *compiler);
    Token *next_token();

    bool parse_axiom();

    bool parse_kw(string keyword);
};

#endif //LAB71_SCANNER_H
