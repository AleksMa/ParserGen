#ifndef LAB5_TOKEN_H
#define LAB5_TOKEN_H

#include <string>
#include "../Position/Fragment.h"
#include "../NameMap.h"

using namespace std;

class Token {
public:
    virtual string to_str();
    domain_tag get_tag();

protected:
    domain_tag tag;
    Fragment coords;

    Token(domain_tag type, Position start, Position end);

    //domain_tag get_type();
};


#endif //LAB5_TOKEN_H
