
#ifndef LAB71_RULESMAP_H
#define LAB71_RULESMAP_H

#include "Utils/NameMap.h"
#include <vector>
#include <map>

using namespace std;

map<pair<rule, domain_tag>, vector<pair<bool, int>>> D =
        {{{GRAMMAR, NT_KW}, {{0, NT_DEC}, {0, T_DEC}, {0, R_LIST}, {0, A}, {1, END_OF_PROGRAM}, }},
         {{NT_DEC, NT_KW}, {{1, NT_KW}, {0, NT_LIST}, {1, SEMICOLON}, }},
         {{NT_LIST, NON_TERM}, {{1, NON_TERM}, {0, NT_TAIL}, }},
         {{NT_TAIL, SEMICOLON}, {}},
         {{NT_TAIL, COMMA}, {{1, COMMA}, {1, NON_TERM}, {0, NT_TAIL}, }},
         {{T_DEC, T_KW}, {{1, T_KW}, {0, T_LIST}, {1, SEMICOLON}, }},
         {{T_LIST, TERM}, {{1, TERM}, {0, T_TAIL}, }},
         {{T_TAIL, SEMICOLON}, {}},
         {{T_TAIL, COMMA}, {{1, COMMA}, {1, TERM}, {0, T_TAIL}, }},
         {{R_LIST, NON_TERM}, {{0, RULE}, {0, RULE_TAIL}, }},
         {{RULE, NON_TERM}, {{1, NON_TERM}, {1, ID_EST}, {0, RIGHT_SEC}, {0, RIGHT_TAIL}, {1, SEMICOLON}, }},
         {{RIGHT_SEC, NON_TERM}, {{1, NON_TERM}, {0, RIGHT_SUB}, }},
         {{RIGHT_SEC, TERM}, {{1, TERM}, {0, RIGHT_SUB}, }},
         {{RIGHT_SEC, EPSILON}, {{1, EPSILON}, }},
         {{RIGHT_SUB, NON_TERM}, {{1, NON_TERM}, {0, RIGHT_SUB}, }},
         {{RIGHT_SUB, TERM}, {{1, TERM}, {0, RIGHT_SUB}, }},
         {{RIGHT_SUB, SEMICOLON}, {}},
         {{RIGHT_SUB, OR}, {}},
         {{RIGHT_SUB, EPSILON}, {{1, EPSILON}, }},
         {{RIGHT_TAIL, SEMICOLON}, {}},
         {{RIGHT_TAIL, OR}, {{1, OR}, {0, RIGHT_SEC}, {0, RIGHT_TAIL}, }},
         {{RULE_TAIL, NON_TERM}, {{0, RULE}, {0, RULE_TAIL}, }},
         {{RULE_TAIL, AXIOM}, {}},
         {{A, AXIOM}, {{1, AXIOM}, {1, NON_TERM}, {1, SEMICOLON}, }},
        };


#endif //LAB71_RULESMAP_H