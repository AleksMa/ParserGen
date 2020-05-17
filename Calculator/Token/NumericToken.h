//
// Created by a.mamaev on 09.03.2020.
//

#ifndef LEXERLAB4_NUMERICTOKEN_H
#define LEXERLAB4_NUMERICTOKEN_H


#include "../../Utils/Token/Token.h"

class NumericToken: public Token {
public:
    int val;

    NumericToken(int num, Position start, Position end);

    string to_str() override;
};


#endif //LEXERLAB4_NUMERICTOKEN_H
