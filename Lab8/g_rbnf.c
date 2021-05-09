non-terminal    GRAMMAR, NT_DEC, NT_LIST, T_DEC, T_LIST, R_LIST, RIGHT_SEC, RIGHT_TERM;
terminal        'non_term', 'term', ';', '|', '::=', ',', 'epsilon', '(', ')', '*', 'non-terminal', 'terminal';

GRAMMAR     ::= NT_DEC T_DEC R_LIST;

NT_DEC      ::= 'non-terminal' NT_LIST ';' ;
NT_LIST     ::= 'non_term' ( ',' 'non_term' )*;

T_DEC       ::= 'terminal' T_LIST ';' ;
T_LIST      ::= 'term' ( ',' 'term' )*;

R_LIST      ::= ('non_term' '::=' RIGHT_SEC ';')*;
RIGHT_SEC   ::= RIGHT_TERM ( RIGHT_TERM )* ( '|' RIGHT_SEC);
RIGHT_TERM  ::= 'non_term' | 'term' | 'epsilon' | '(' RIGHT_SEC ')' ('*')?;