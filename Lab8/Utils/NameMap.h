//
// Created by a.mamaev on 10.05.2020.
//

#ifndef LAB71_NAMEMAP_H
#define LAB71_NAMEMAP_H

#pragma once

#include <map>

static const int END_OF_PROGRAM = -1;

enum rule {
    GRAMMAR,
    NT_DEC,
    NT_LIST,

    T_DEC,
    T_LIST,

    R_LIST,
    RIGHT_SEC,
    RIGHT_SUB,
    RIGHT_TERM,
};


enum domain_tag {
    NON_TERM,       // 0
    TERM,           // 1
    AXIOM,          // 2
    SEMICOLON,      // 3
    OR,             // 4
    ID_EST,         // 5
    COMMA,          // 6
    EPSILON,        // 7
    NT_KW,          // 8
    T_KW,           // 9
    L_PAR,          // 10
    R_PAR,          // 11
    STAR,           // 12
};

enum calc_domain_tag {
    SUM,            // 0
    SUB,            // 1
    MUL,            // 2
    DIV,            // 3
    LPAR,           // 4
    RPAR,           // 5
    N,              // 6
};

enum calc_rule {
    E,
    T,
    F,
};

static map<int, string> calc_rule_names = {
        {E,  "E"},
        {T,  "T"},
        {F,  "F"},
};

static map<int, string> token_names = {
        {NON_TERM,       "NON_TERM"},
        {TERM,           "TERM"},
        {AXIOM,          "AXIOM"},
        {SEMICOLON,      "SEMICOLON"},
        {OR,             "OR"},
        {ID_EST,         "ID_EST"},
        {COMMA,          "COMMA"},
        {EPSILON,        "EPSILON"},
        {NT_KW,          "NT_KW"},
        {T_KW,           "T_KW"},
        {END_OF_PROGRAM, "END_OF_PROGRAM"}
};

static map<int, string> calc_token_names = {
        {SUM, "+"},
        {SUB, "-"},
        {MUL, "*"},
        {DIV, "/"},
        {LPAR, "("},
        {RPAR, ")"},
        {N, "N"},
        {END_OF_PROGRAM, "END_OF_PROGRAM"},
};


#endif //LAB71_NAMEMAP_H
