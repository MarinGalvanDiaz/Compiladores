%{
#include   "hoc.h"
#define  code2(c1,c2)	    code(c1);   code(c2)
#define  code3(c1 ,c2,c3)   code(c1);   code(c2); code(c3)
#define  code4(c1 ,c2,c3, c4)   code(c1);   code(c2); code(c3); code(c4) // NUEVA PRACTICA 6
     
/* Los prototipos se movieron a hoc.h */
%}
%union   {
Symbol  *sym;   /* apuntador de la tabla de símbolos */ 
Inst    *inst;  /* instrucción de máquina */
}
/* El token original es INDEF, no UNDEF */
/* ******** MODIFICADO: Añadido FOR ******** */
%token  <sym>   NUMBER PRINT VAR BLTIN INDEF WHILE IF ELSE FOR
/* ******** MODIFICADO: Añadido forstmt ******** */
%type   <inst>  stmt asgn expr stmtlist cond while if end forstmt

%right	'='
%left	OR
%left	AND
%left	GT GE LT LE EQ NE
%left	'+' '_'
%left	'*' '/'
%left	UNARYMINUS NOT
%right	'^'
%%

list:     /* nada */ 
	|
list '\n'
	| list asgn '\n'	{ //puts("list asgn");
                                  code2(pop1, STOP); return 1; }
	| list stmt '\n'	{ code(STOP); return 1; }
	|
list expr '\n'	{ code2(print, STOP); return 1; }
	| list error '\n'	{ yyerrok; }
	;
asgn:     VAR '=' expr  { $$=$3; code3(varpush,(Inst)$1,assign);
}
         ;
stmt:     expr   { code(pop1); $$ = $1; /* CORREGIDO: Propagar $$ */
}
	| PRINT expr    { code(prexpr); $$ = $2;} 
	|
while cond stmt end {
		($1)[1] = (Inst)$3;     /* cuerpo de la iteración */ 
		($1)[2] = (Inst)$4;
        $$ = $1; /* CORREGIDO: Propagar $$ */
}   /* terminar si la condición no se cumple */
   
	|
if cond stmt end {    /* proposición if que no emplea else */ 
		($1)[1] = (Inst)$3;
/* parte then */ 
		($1)[3] = (Inst)$4; 
        $$ = $1; /* CORREGIDO: Propagar $$ */
}   /* terminar si la condición no se cumple */ 
       
	|
if cond stmt end ELSE stmt end {  /* proposición if con parte else */
		($1)[1]   =   (Inst)$3;
/* parte then  */
		($1)[2]   =   (Inst)$6;
/* parte else   */
		($1)[3]   =   (Inst)$7;
        $$ = $1; /* CORREGIDO: Propagar $$ */
} /* terminar si la condición no se cumple  */

    
    | forstmt '(' expr { code(STOP); } ';'  
                    expr { code(STOP); } ';'  
                    expr { code(STOP); } ')'  
                    stmt { code(STOP); } 
            end 
    {
		($1)[1] = (Inst)$3;  
		($1)[2] = (Inst)$6;  
		($1)[3] = (Inst)$9;  
		($1)[4] = (Inst)$12;
		($1)[5] = (Inst)$14; 
        $$ = $1; 
    }

	|
'{'   stmtlist   '}' {   $$  =  $2;
}
        ;
cond:	'('   expr   ')'      {   code(STOP);
$$  =  $2;   }
;
                  //$$ = code(whilecode); code(STOP);  code(STOP);
while:	WHILE   {   $$ = code3(whilecode, STOP, STOP); }
	;
if:IF   { $$=code(ifcode); code3(STOP, STOP, STOP);
}
	;
/* ******** NUEVA REGLA FOR (PRACTICA 6) ******** */
/* 5 STOPS (init, cond, inc, body, end) */
forstmt: FOR { $$ = code(forcode); code4(STOP, STOP, STOP, STOP); code(STOP); }
	;

/* ******** REGLA 'end' CORREGIDA ******** */
end:      /* nada */{ $$ = progp; code(STOP); } /* Se asigna $$ ANTES de añadir el STOP */
	;

/* ******** REGLAS 'stmtlist' CORREGIDAS ******** */
stmtlist: /* nada */	{ $$ = progp; }
	| stmtlist '\n' { $$ = $1; } /* CORREGIDO: Propagar $$ */
	| stmtlist stmt { $$ = $1; } /* CORREGIDO: Propagar $$ */
	;
expr:    NUMBER { $$ = code2(constpush, (Inst)$1); }
/* ******** LÍNEA CORREGIDA ******** */
	| VAR	{  $$ = code3(varpush, (Inst)$1, eval);}
	| asgn
	|
BLTIN '(' expr ')'
	{ $$ = $3; code2(bltin,(Inst)$1->u.ptr); }
	|	'(' expr ')'  { $$ = $2;
}
	|expr '+' expr { code(add); }
	|expr '-' expr { code(sub); }
	|expr '*' expr { code(mul); }
/* MODIFICADO: Llamar a c_div en lugar de div */
	|expr '/' expr { code(c_div);
}
	|expr '^' expr { code (power); }
	|'-' expr %prec UNARYMINUS  { $$ = $2; code(negate);
}
	|expr GT expr  { code(gt); }
	|expr GE expr  { code(ge); }
	|expr LT expr  { code(lt);
}
	|expr LE expr  { code(le); }
	|expr EQ expr  { code (eq); }
	|expr NE expr  { code(ne);
}
	|expr AND expr { code(and); }
	|expr OR expr  { code(or);
}
	|NOT expr      { $$ = $2; code(not); }
	;
%%
/* NUEVO: Includes necesarios para la sección de código C */
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
#include "y.tab.h" /* <-- ESTE ES EL MÁS IMPORTANTE (define INDEF, etc.) */


jmp_buf begin;
char *progname;
int lineno = 1;

/* MODIFICADO: Añadido 'int' */
int main(int argc, char **argv)       /* hoc5 */ 
{
/*int  fpecatch();*/
progname  =  argv[0];
init( );
setjmp(begin);
signal(SIGFPE, fpecatch);
for (initcode(); yyparse(); initcode() )
execute(prog); 
return 0; 
}

/* MODIFICADO: Añadido 'int' y 'void' */
int yylex(void){
int c;
while  ((c=getchar()) ==  ' ' ||  c ==   '\t')
          ;
if (c == EOF)
	return 0; 
if (c == '.' || isdigit(c)) {   /* número */
	double d_real;
	Complejo d_comp; // NUEVO
	
	ungetc(c, stdin);
	scanf("%lf", &d_real);

	/* MODIFICADO: Instalar como (real, 0) */
	d_comp.real = d_real; 
	d_comp.imag = 0.0;
	yylval.sym = install("", NUMBER, d_comp); /* MODIFICADO */
	
	return NUMBER; 
}
if (isalpha(c)) { 
	Symbol *s;
	char sbuf[100], *p = sbuf; 
	do {
		if (p >= sbuf + sizeof(sbuf) - 1) { 
			*p = '\0'; 
			execerror("name too long", sbuf);
		}
	*p++ = c;
	} while ((c=getc(stdin)) != EOF && isalnum(c)); 
	ungetc(c, stdin); 
	*p = '\0';
	if ((s=lookup(sbuf)) == 0) {
       		/* MODIFICADO: Instalar INDEF con (0, 0) */
			Complejo d_zero = {0.0, 0.0};
       		s=install(sbuf, INDEF, d_zero); 
	}
	yylval.sym = s;
	/* MODIFICADO: Usar INDEF */
	return s->type == INDEF ? VAR : s->type;
}
	switch (c) {
	case '>':                return follow('=', GE, GT);
	case '<':                return follow('=', LE, LT);
	case '=':                return follow('=', EQ, '=');
	case '!':                return follow('=', NE, NOT);
	case '|':                return follow('|', OR, '|');
	case '&':                return (follow('&', AND, '&'));
	case '\n':              lineno++; return '\n';
	default:                  return c;
	}
}
/* FIN DE MODIFICACIÓN en yylex */


/* MODIFICADO: Añadido 'int' */
int follow(int expect,   int ifyes,   int ifno)  { /* buscar  >=, etc.   */ 
   int c  = getchar();
if  (c  ==  expect)
      return ifyes; 
   ungetc(c,   stdin);
return  ifno;
}

void yyerror(char *s)      /* comunicar errores de tiempo de compilación */
{
warning(s, (char *)0);
} 

void execerror(char *s, char *t){
	warning(s, t);
	longjmp(begin, 0);
}
void fpecatch(int e)      /* detectar errores por punto flotante */ 
{
execerror("floating point exception", (char *) 0);
}	

void warning(char *s, char *t){
	fprintf (stderr, "%s: %s", progname, s);
	if(t)
		fprintf (stderr, " %s", t);
	fprintf (stderr, "cerca de la linea %d\n", lineno);
}
