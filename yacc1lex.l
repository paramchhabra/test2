%{
#include "yacc1.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*  { yylval = strdup(yytext); return IDENTIFIER; }
\n                    { return EOL; }
.                     { /* ignore other characters */ }
%%

int yywrap() {
    return 1;
}
