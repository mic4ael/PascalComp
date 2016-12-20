%{

#include <math.h>

int lineno = 1;

%}

LETTER [a-zA-Z]
DIGIT [0-9]
ID LETTER (LETTER | DIGIT)*
DIGITS DIGIT DIGIT*
OPTIONAL_FRACTION . DIGITS?
OPTIONAL_EXPONENT (E (+ | -)? DIGITS)?
NUM DIGITS OPTIONAL_FRACTION OPTIONAL_EXPONENT
ASSIGNOP :=
OROP or
NEWLINE \n
TAB \t
SPACE " "

%%

{SPACE} |
{TAB} /* ignore */

{NEWLINE} lineno++;


<<EOF>> return DONE;

. {

}

%%

=, <>, <, <=, >=, and >.
+ or -.
*, /, div, mod, and and.
