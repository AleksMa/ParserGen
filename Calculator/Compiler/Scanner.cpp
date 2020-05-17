#include "Scanner.h"
#include "Compiler.h"
#include "../Token/NumericToken.h"
#include "../Token/SpecToken.h"

#include <string>

using namespace std;

Scanner::Scanner(string source, Compiler *compiler) : program(source + char(-1)), cur(source + char(-1)),
                                                      compiler(compiler) {}

int Scanner::parse_val() {
    int val = cur.cp() - '0';
    while ((++cur).is_digit()) {
        val = val * 10 + cur.cp() - '0';
    }
    return val;
}


Token *Scanner::next_token() {
    while (cur.cp() != -1) {
        while (cur.is_whitespace() || cur.is_newline())
            cur++;
        Position start = cur;

        switch (cur.cp()) {
            case '+':
                return new SpecToken(SUM, start, ++cur);
            case '*':
                return new SpecToken(MUL, start, ++cur);
            case '(':
                return new SpecToken(LPAR, start, ++cur);
            case ')':
                return new SpecToken(RPAR, start, ++cur);
            default:
                if (cur.is_digit()) {
                    int val = parse_val();
                    return new NumericToken(val, start, cur);
                } else {
                    compiler->add_message(true, cur++, "Unexpected character");
                    break;
                }
        }
    }
    return new SpecToken(END_OF_PROGRAM, cur, cur);
}