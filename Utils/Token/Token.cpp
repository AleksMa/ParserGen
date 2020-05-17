#include "Token.h"

#include <utility>

Token::Token(domain_tag type, Position start, Position end) :
        tag(type), coords(start, end) {}

string Token::to_str() {
    return to_string(tag) + " " + coords.to_str();
}

domain_tag Token::get_tag() {
    return tag;
}
