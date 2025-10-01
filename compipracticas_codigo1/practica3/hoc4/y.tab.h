#define NUMBER 257
#define VAR 258
#define BLTIN 259
#define INDEF 260
#define UNARYMINUS 261
typedef union {
	Symbol *sym;
	Inst *inst;
} YYSTYPE;
extern YYSTYPE yylval;
