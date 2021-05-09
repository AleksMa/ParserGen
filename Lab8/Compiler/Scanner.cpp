#include "Scanner.h"
#include "Compiler.h"
#include "../Token/NonTermToken.h"
#include "../Token/TermToken.h"
#include "../Token/SpecToken.h"

#include <string>

using namespace std;

Scanner::Scanner(string source, Compiler *compiler) : program(source + char(-1)), cur(source + char(-1)),
                                                      compiler(compiler) {}

long Scanner::parse_val() {
    long val = cur.cp() - '0';
    while ((++cur).is_digit()) {
        val = val * 10 + cur.cp() - '0';
    }
    return val;
}

bool Scanner::parse_kw(string keyword) {
    int i = 0;
    while (!cur.is_newline() && !cur.is_whitespace() && i < keyword.size()) {
        if (cur.cp() == keyword[i]) {
            cur++;
            i++;
        } else {
            return false;
        }
    }
    return !cur.is_letter() && !cur.is_digit();
}


Token *Scanner::next_token() {
    while (cur.cp() != -1) {
        while (cur.is_whitespace() || cur.is_newline())
            cur++;
        Position start = cur;

        switch (cur.cp()) {
            case ';':
                return new SpecToken(SEMICOLON, start, ++cur);
            case '|':
                return new SpecToken(OR, start, ++cur);
            case ',':
                return new SpecToken(COMMA, start, ++cur);
            case ')':
                return new SpecToken(R_PAR, start, ++cur);
            case '(':
                return new SpecToken(L_PAR, start, ++cur);
            case '*':
                return new SpecToken(STAR, start, ++cur);
            case ':':
                cur++;
                if (cur.cp() != ':') {
                    compiler->add_message(true, start, "Term");
                    break;
                }
                cur++;
                if (cur.cp() != '=') {
                    compiler->add_message(true, start, "Term");
                    break;
                }
                return new SpecToken(ID_EST, start, ++cur);
            case '\'': {
                bool err = false;
                do {
                    if (cur.cp() != '\n')
                        cur++;
                    else {
                        compiler->add_message(true, start, "Unexpected character");
                        while (cur.cp() != '\'' && cur.cp() != -1)
                            cur++;
                        err = true;
                        break;
                    }
                } while (cur.cp() != '\'');
                cur++;
                if (!err) {
                    string ident = program.substr(start.get_index(), cur.get_index() - start.get_index());
                    compiler->add_name(ident);
                    return new TermToken(ident, start, cur);
                }
                break;
            }
            default:
                if (cur.is_letter()) {
                    char c = cur.cp();
                    if (parse_kw("axiom")) {
                        return new SpecToken(AXIOM, start, cur);
                    }
                    if (parse_kw("non-terminal")) {
                        return new SpecToken(NT_KW, start, cur);
                    }
                    if (parse_kw("terminal")) {
                        return new SpecToken(T_KW, start, cur);
                    }
                    if (parse_kw("epsilon")) {
                        return new SpecToken(EPSILON, start, cur);
                    }
                    if (cur.is_high_letter()) {
                        while (cur.is_high_letter() || cur.cp() == '_') {
                            cur++;
                        }
                        while (cur.is_digit()) {
                            cur++;
                        }
                        if (!cur.is_letter() && !cur.is_digit()) {
                            string ident = program.substr(start.get_index(), cur.get_index() - start.get_index());
                            compiler->add_name(ident);
                            return new NonTermToken(ident, start, cur);
                        }
                    }
                } else {
                    cur++;
                    compiler->add_message(true, start, "Unexp");
                    break;
                }
        }
    }
    return new SpecToken(END_OF_PROGRAM, cur, cur);
}