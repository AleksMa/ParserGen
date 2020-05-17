#ifndef LAB71_SPECTOKEN_H
#define LAB71_SPECTOKEN_H

#include "../../Utils/Token/Token.h"

class SpecToken: public Token {
public:
    string to_str() override;

    SpecToken(int tag, Position start, Position end);
};


#endif //LAB71_SPECTOKEN_H
