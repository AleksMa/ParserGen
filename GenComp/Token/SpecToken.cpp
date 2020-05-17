#include "SpecToken.h"

SpecToken::SpecToken(domain_tag tag, Position start, Position end): Token(tag, start, end) {}

string SpecToken::to_str() {
    string type = "END OF PROGRAM";
    switch(tag) {
        case AXIOM:
            type = "AXIOM         ";
            break;
        case SEMICOLON:
            type = "SEMICOLON     ";
            break;
        case OR:
            type = "OR            ";
            break;
        case EPSILON:
            type = "EPSILON       ";
            break;
        case NT_KW:
            type = "NT_KW         ";
            break;
        case T_KW:
            type = "T_KW          ";
            break;
        case COMMA:
            type = "COMMA         ";
            break;
        case ID_EST:
            type = "ID_EST        ";
            break;
    }
    return type + " " + coords.to_str();
}