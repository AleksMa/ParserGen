//
// Created by a.mamaev on 09.03.2020.
//

#include "NumericToken.h"

NumericToken::NumericToken(int num, Position start, Position end): Token(N, start, end), val(num) {}

string NumericToken::to_str() {
    return "N              " + coords.to_str() + ": " + to_string(val);
}
