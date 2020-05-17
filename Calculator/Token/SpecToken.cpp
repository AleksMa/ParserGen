#include "SpecToken.h"

SpecToken::SpecToken(int tag, Position start, Position end): Token(tag, start, end) {}

string SpecToken::to_str() {
    string type = "END OF PROGRAM";
    switch(tag) {
        case SUM:
            type = "SUM           ";
            break;
        case MUL:
            type = "MUL           ";
            break;
        case LPAR:
            type = "LPAR          ";
            break;
        case RPAR:
            type = "RPAR          ";
            break;
        case N:
            type = "NUMERIC       ";
            break;
    }
    return type + " " + coords.to_str();
}