/* Compiler Theory and Design
   Duane J. Jarc */

/* This file contains flex input file */

/* Edited by Sean Filer on 12/13/2019 */

%{
#include <string>

using namespace std;

#include "types.h"
#include "listing.h"
#include "tokens.h"

%}

%option noyywrap

ws		[ \t\r]+
dashcomment	\-\-.*\n
slashcomment	\/\/.*\n
comment		{dashcomment}|{slashcomment}
line		[\n]
id		[A-Za-z](_?[A-Za-z0-9]+)*
digit		[0-9]
int		{digit}+
real		{int}\.{int}?([eE]\-?{int})?
punc		[\(\),:;]
bool		true|false
relop		([/><]?=)|[><]
addop		[\+\-]
mulop		[\*\/]
remop		rem
expop		\*\*
arrow		=>
%%

{ws}		{ ECHO; }
{comment}	{ ECHO; nextLine();}
{line}		{ ECHO; nextLine();}
{arrow}		{ ECHO; return(ARROW); }
{relop}		{ ECHO; return(RELOP); }
{addop}		{ ECHO; return(ADDOP); }
{mulop}		{ ECHO; return(MULOP); }
{remop}		{ ECHO; return(REMOP); }
{expop}		{ ECHO; return(EXPOP); } 
{arrow}		{ ECHO; return(ARROW); }
and		{ ECHO; return(ANDOP); }
begin		{ ECHO; return(BEGIN_); }
boolean		{ ECHO; return(BOOLEAN); }
case		{ ECHO; return(CASE); }
else		{ ECHO; return(ELSE); }
end		{ ECHO; return(END); }
endcase		{ ECHO; return(ENDCASE); }
endif		{ ECHO; return(ENDIF); }
endreduce	{ ECHO; return(ENDREDUCE); }
function	{ ECHO; return(FUNCTION); }
if		{ ECHO; return(IF); }
integer		{ ECHO; return(INTEGER); }
is		{ ECHO; return(IS); }
not		{ ECHO; return(NOTOP); }
or		{ ECHO; return(OROP); }
reduce		{ ECHO; return(REDUCE); }
real		{ ECHO; return(REAL); }
returns		{ ECHO; return(RETURNS); }
then		{ ECHO; return(THEN); }
when		{ ECHO; return(WHEN); }
{bool}		{ ECHO; yylval.type = BOOL_TYPE; return(BOOL_LITERAL); }
{id}		{ ECHO; yylval.iden = (CharPtr)malloc(yyleng + 1); 
			strcpy(yylval.iden, yytext); return(IDENTIFIER); }
{real}		{ ECHO; yylval.type = REAL_TYPE; return(REAL_LITERAL); }
{int}		{ ECHO; yylval.type = INT_TYPE; return(INT_LITERAL); }
{punc}		{ ECHO; return(yytext[0]); }
.		{ ECHO; appendError(LEXICAL, yytext); }

%%
