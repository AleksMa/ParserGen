non-terminal    E, T, F;
terminal        '+', '-', '*', '/', '(', ')', 'n';
E           ::= T ( ( '+' | '-' ) T )*;
T           ::= F ( ( '*' | '/' ) F )*;
F           ::= 'n' | '-' F | '(' E ')';