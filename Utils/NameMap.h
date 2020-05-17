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
    NT_TAIL,

    T_DEC,
    T_LIST,
    T_TAIL,

    R_LIST,
    RULE,
    RIGHT_SEC,
    RIGHT_SUB,
    RIGHT_TAIL,
    RULE_TAIL,
    A,
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
};

enum calc_domain_tag {
    SUM,            // 0
    MUL,            // 1
    LPAR,           // 2
    RPAR,           // 3
    N,              // 4
};

enum calc_rule {
    E,
    E1,
    T,
    T1,
    F,
};

static map<int, string> rule_names = {
        {GRAMMAR,    "GRAMMAR"},
        {NT_DEC,     "NT_DEC"},
        {NT_LIST,    "NT_LIST"},
        {NT_TAIL,    "NT_TAIL"},

        {T_DEC,      "T_DEC"},
        {T_LIST,     "T_LIST"},
        {T_TAIL,     "T_TAIL"},

        {R_LIST,     "R_LIST"},
        {RULE,       "RULE"},
        {RIGHT_SEC,  "RIGHT_SEC"},
        {RIGHT_SUB,  "RIGHT_SUB"},
        {RIGHT_TAIL, "RIGHT_TAIL"},
        {RULE_TAIL,  "RULE_TAIL"},
        {A,          "A"}
};

static map<int, string> calc_rule_names = {
        {E,  "E"},
        {E1, "E1"},
        {T,  "T"},
        {T1, "T1"},
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
        {SUM, "SUM"},
        {MUL, "MUL"},
        {LPAR, "LPAR"},
        {RPAR, "RPAR"},
        {N, "N"},
        {END_OF_PROGRAM, "END_OF_PROGRAM"},
};


#endif //LAB71_NAMEMAP_H
