#include <iostream>
#include "Compiler.h"
#include "Scanner.h"

using namespace std;

Compiler::Compiler() = default;

int Compiler::add_name(string name) {
    if (name_codes.find(name) == name_codes.end()) {
        int code = name_codes.size();
        name_codes[name] = code;
        return code;
    }
    return name_codes[name];
}

string Compiler::get_name(int code) {
    return names[code];
}

void Compiler::add_message(bool is_error, Position c, string text) {
    messages.emplace_back(c, Message(is_error, text));
}

void Compiler::output_messages() {
    for (auto message : messages) {
        cout << (message.second.get_error() ? "E" : "W");
        cout << " " << message.first.to_str();
        cout << ": " << message.second.get_text() << endl;
    }
}

Scanner Compiler::get_scanner(string program) {
    return Scanner(program, this);
}

Parser Compiler::get_parser(Scanner lex) {
    return Parser(lex);
}

Compiler::~Compiler() {}
