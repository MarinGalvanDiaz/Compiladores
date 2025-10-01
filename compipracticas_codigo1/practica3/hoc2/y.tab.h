#define NUMBER 257
#define VAR 258
#define UNARYMINUS 259
typedef union {
	double val; /*val es el valor que se va almac. en alguna posi arreglo*/
	int index; /*posicion en el arreglo*/
} YYSTYPE;
extern YYSTYPE yylval;
