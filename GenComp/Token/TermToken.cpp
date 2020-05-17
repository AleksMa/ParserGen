#include "TermToken.h"

TermToken::TermToken(string ident, Position start, Position end): Token(TERM, start, end), ident(ident) {}

string TermToken::to_str() {
    return "TERMINAL       " + coords.to_str() + ": " + ident;
}
