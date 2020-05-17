#ifndef LAB71_TERMTOKEN_H
#define LAB71_TERMTOKEN_H

#include <string>
#include "Token.h"

using namespace std;


class TermToken: public Token {

public:
    string to_str() override;
    string ident;

    TermToken(string ident, Position start, Position end);
};


#endif //LAB71_TERMTOKEN_H
