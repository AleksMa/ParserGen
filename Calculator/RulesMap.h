#ifndef LAB71_RULESMAP_H
#define LAB71_RULESMAP_H

#include "../Utils/NameMap.h"
#include <vector>
#include <map>

using namespace std;


map<pair<int, int>, vector<pair<bool, int>>> D =
        {{{E,  LPAR},           {{0, T},    {0, E1},}},
         {{E,  N},              {{0, T},    {0, E1},}},
         {{E1, END_OF_PROGRAM}, {}},
         {{E1, SUM},            {{1, SUM},  {0, T}, {0, E1},}},
         {{E1, RPAR},           {}},
         {{T,  LPAR},           {{0, F},    {0, T1},}},
         {{T,  N},              {{0, F},    {0, T1},}},
         {{T1, END_OF_PROGRAM}, {}},
         {{T1, SUM},            {}},
         {{T1, MUL},            {{1, MUL},  {0, F}, {0, T1},}},
         {{T1, RPAR},           {}},
         {{F,  LPAR},           {{1, LPAR}, {0, E}, {1, RPAR},}},
         {{F,  N},              {{1, N},}},
        };


//map<pair<int, int>, vector<pair<bool, int>>> D =
//        {{{E,  LPAR},           {{0, T},    {0, E1}, {1, END_OF_PROGRAM},}},
//         {{E,  N},              {{0, T},    {0, E1}, {1, END_OF_PROGRAM},}},
//         {{E1, SUM},            {{1, SUM},  {0, T},  {0, E1},}},
//         {{E1, END_OF_PROGRAM}, {}},
//         {{T,  LPAR},           {{0, F},    {0, T1},}},
//         {{T,  N},              {{0, F},    {0, T1},}},
//         {{T1, SUM},            {}},
//         {{T1, MUL},            {{1, MUL},  {0, F},  {0, T1},}},
//         {{T1, END_OF_PROGRAM}, {}},
//         {{F,  LPAR},           {{1, LPAR}, {0, E},  {1, RPAR},}},
//         {{F,  N},              {{1, N},}},
//        };


#endif //LAB71_RULESMAP_H