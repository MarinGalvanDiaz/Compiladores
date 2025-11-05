// NUEVO: Definición de Complejo
typedef struct {
    double real;
    double imag;
} Complejo;

typedef struct Symbol { /* entrada en la tabla de símbolos */
char    *name;
// MODIFICADO: El token es INDEF, no UNDEF
short   type;   /* VAR, BLTIN, INDEF */
union {
// MODIFICADO: de double a Complejo
Complejo val;	/* si es VAR */
// MODIFICADO: (double (*)(double)) -> (Complejo (*)(Complejo))
Complejo  (*ptr)(Complejo);       /* si es BLTIN */
} u;
struct Symbol   *next;  /* para ligarse a otro */ } Symbol;
Symbol  *install(), *lookup();

typedef union Datum {   /* tipo de la pila del intérprete */
// MODIFICADO: de double a Complejo
Complejo  val;
// NUEVO: para resultados lógicos
double dval; 
Symbol  *sym; 
} Datum; 

extern Datum pop();

typedef void (*Inst)(void);  /* instrucción de maquina */ 

#define STOP    (Inst) 0

extern	Inst prog[ ] , *progp, *code();

extern	void eval();
extern	void add();
extern	void sub(); 
extern	void mul(); 
// MODIFICADO: Renombrado para evitar conflicto con stdlib.h
extern	void c_div(); 
extern	void negate(); 
extern	void power();
extern	void assign(); 
extern	void bltin(); 
extern	void varpush(); 
extern	void constpush();
extern	void print();
extern	void pop1();

extern	void prexpr();
extern	void gt();
extern	void lt(); 
extern	void eq(); 
extern	void ge(); 
extern	void le(); 
extern	void ne(); 
extern	void and(); 
extern	void or();
extern	void not();
extern	void ifcode(); 
extern	void whilecode();
extern	void forcode(); /* ******** NUEVO PROTOTIPO (PRACTICA 6) ******** */
void execute(Inst *p);

/* NUEVO: Prototipos de funciones auxiliares */
void init(void);
void initcode(void);
int yylex(void);
int yyparse(void);
void execerror(char *s, char *t);
void warning(char *s, char *t);
int follow(int expect, int ifyes, int ifno);
char *emalloc(unsigned n);
double errcheck(double d, char *s);
double Pow(double x, double y);
double Log(double x);
double Log10(double x);
double Sqrt(double x);
double Exp(double x);
double integer(double x);
void fpecatch(int e);
// NUEVO: Prototipo para yyerror
void yyerror(char *s); 
/* Fin de nuevos prototipos */
