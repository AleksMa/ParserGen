#include "NonTermToken.h"

NonTermToken::NonTermToken(string ident, Position start, Position end): Token(NON_TERM, start, end), ident(ident) {}

string NonTermToken::to_str() {
    return "NON_TERMINAL   " + coords.to_str() + ": " + ident;
}
