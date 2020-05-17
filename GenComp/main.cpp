/*
non-terminal E , E1 , T , T1 , F ;
terminal '+ ' , '* ' , '( ' , ') ' , n ;
E ::= T E1 ;
E1 ::= '+' T E1 | epsilon ;
T ::= F T1 ;
T1 ::= '* ' F T1 | epsilon ;
F ::= n | '( ' E ') ';
axiom E ;
 */


/*
NT ~ identifier   [A-Z]+[0-9]*
non-terminal
terminal
axiom
;
|
::=
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

    bool calculator_gram = false;

    if (argc == 3 && argv[2] != "0")
        calculator_gram = true;

    Compiler generator(calculator_gram);

    Scanner lex = generator.get_scanner(source);

    Parser parser = Parser(lex, D);

    parser.parse();

    //parser.print_tree();

    ResultNode *ast = generator.makeAST(parser.get_root());

    generator.print_tree(ast);

    generator.create_grammar(ast);

    if (generator.has_error())
        cout << generator.get_error() << endl;

    return 0;
}
