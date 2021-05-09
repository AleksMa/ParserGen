#ifndef LAB5_TOKEN_H
#define LAB5_TOKEN_H

#include <string>
#include "../Position/Fragment.h"
#include "../NameMap.h"

using namespace std;

class Token {
public:
    virtual string to_str();
    int get_tag();

protected:
    int tag;
    Fragment coords;

    Token(int type, Position start, Position end);

    //domain_tag get_type();
};


#endif //LAB5_TOKEN_H
