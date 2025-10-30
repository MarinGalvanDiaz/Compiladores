#ifndef HOC_H
#define HOC_H

#include <math.h>  // Para pow()

/* Constantes para tipos de símbolos - usar nombres únicos */
#define HOC_UNDEF   0
#define HOC_VAR     1
#define HOC_BLTIN   2
#define HOC_NUMBER  3

/* Constantes para palabras clave - usar nombres únicos */
#define HOC_IF     260
#define HOC_ELSE   261
#define HOC_WHILE  262
#define HOC_PRINT  263
#define HOC_OR     264
#define HOC_AND    265
#define HOC_GT     266
#define HOC_GE     267  
#define HOC_LT     268
#define HOC_LE     269
#define HOC_EQ     270
#define HOC_NE     271
#define HOC_NOT    272

/* Tamaño del programa */
#define NPROG  1000

typedef struct Symbol { /* entrada en la tabla de símbolos */
    char    *name;
    short   type;   /* HOC_VAR, HOC_BLTIN, HOC_UNDEF */
    union {
        double val;    /* si es HOC_VAR */
        double  (*ptr)(double);       /* si es HOC_BLTIN */
    } u;
    struct Symbol   *next;  /* para ligarse a otro */ 
} Symbol;

Symbol  *install(char *s, int t, double d);
Symbol  *lookup(char *s);

typedef union Datum {   /* tipo de la pila del intérprete */
    double  val;
    Symbol  *sym; 
} Datum;

extern Datum pop();
extern void push(Datum d);

typedef void (*Inst)(void);  /* instrucción de maquina */ 

#define STOP    (Inst) 0

extern Inst prog[], *progp, *code();
extern void execute(Inst *p);

/* Instrucciones de la máquina virtual */
extern void eval();
extern void add();
extern void sub(); 
extern void mul(); 
extern void divide(); 
extern void negate(); 
extern void power();
extern void assign(); 
extern void bltin(); 
extern void varpush(); 
extern void constpush();
extern void print();
extern void pop1();

extern void prexpr();
extern void gt();
extern void lt(); 
extern void eq(); 
extern void ge(); 
extern void le(); 
extern void ne(); 
extern void and();
extern void or();
extern void not();
extern void ifcode(); 
extern void whilecode();

/* Instrucciones para vectores */
extern void assignelem();
extern void evalelem();
extern void createvector();
extern void addtovector();

#endif /* HOC_H */