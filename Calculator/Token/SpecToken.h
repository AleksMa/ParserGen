#ifndef LAB71_SPECTOKEN_H
#define LAB71_SPECTOKEN_H

#include "Token.h"

class SpecToken: public Token {
public:
    string to_str() override;

    SpecToken(domain_tag tag, Position start, Position end);
};


#endif //LAB71_SPECTOKEN_H
