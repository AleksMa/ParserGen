non-terminal E, E1, T, T1, F;
terminal '+', '*', '(', ')', 'n';
E ::= T E1;
E1 ::= '+' T E1 | epsilon;
T ::= F T1;
T1 ::= '*' F T1 | epsilon;
F ::= 'n' | '(' E ')';
axiom E;