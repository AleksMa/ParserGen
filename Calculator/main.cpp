/*
tokens: + * ( ) [0-9]*
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include "Compiler/Compiler.h"
#include "Compiler/Parser.h"
#include "RulesMap.h"

string read_file(const string &path) {
    ifstream source_stream(path);
    ostringstream string_stream;

    string_stream << source_stream.rdbuf();
    source_stream.close();

    return string_stream.str();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Expected: input file" << endl;
        return 0;
    }
    string input_file = argv[1];
    string source = read_file(input_file);

    Compiler compiler;

    Scanner lex = compiler.get_scanner(source);

    Parser parser = Parser(lex, D);

    parser.parse();

    // parser.print_tree();

    ResultNode *ast = compiler.makeAST(parser.get_root());

    compiler.print_tree(ast);

    int res = compiler.calculate(ast);

    cout << endl << "Result: " << res << endl;

    return 0;
}
