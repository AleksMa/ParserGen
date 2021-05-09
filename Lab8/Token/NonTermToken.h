#ifndef LAB71_NONTERMTOKEN_H
#define LAB71_NONTERMTOKEN_H

#include <string>
#include "../Utils/Token/Token.h"

using namespace std;


class NonTermToken: public Token {

public:
    string to_str() override;
    string ident;

    NonTermToken(string ident, Position start, Position end);
};


#endif //LAB71_NONTERMTOKEN_H
