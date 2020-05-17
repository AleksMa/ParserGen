#include "Position.h"
#include <string>



Position::Position(string source): source(source) {
    index = 0;
    pos = line = 1;
}

Position &Position::operator++() {
    if (index < source.size()) {
        if(is_newline()) {
            if (source[index] == '\r')
                index++;
            line++;
            pos = 1;
        } else {
            pos++;
        }
        index++;
    }
    return *this;
}

Position Position::operator++(int) {
    Position ret(*this);
    ++(*this);
    return ret;
}

char Position::cp() {
    return index < source.size() ? source[index] : -1;
}

string Position::to_str() {
    return "(" + to_string(line) + ", " + to_string(pos) + ")";
}

bool Position::is_whitespace() {
    return index < source.size() && (cp() == ' ' || cp() == '\t');
}

bool Position::is_letter() {
    return index < source.size() && isalpha(cp());
}

bool Position::is_high_letter() {
    return is_letter() && cp() >= 'A' && cp() <= 'Z';
}



bool Position::is_digit() {
    return index < source.size() && '0' <= cp() && cp() <= '9';
}

bool Position::is_newline() {
    if (index == source.size())
        return true;
    if (cp() == '\r' && index + 1 < source.size())
        return source[index] == '\n';
    return cp() == '\n';
}

int Position::get_index() {
    return index;
}
