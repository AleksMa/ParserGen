#include "Token.h"

#include <utility>

Token::Token(int type, Position start, Position end) :
        tag(type), coords(start, end) {}

string Token::to_str() {
    return to_string(tag) + " " + coords.to_str();
}

int Token::get_tag() {
    return tag;
}
