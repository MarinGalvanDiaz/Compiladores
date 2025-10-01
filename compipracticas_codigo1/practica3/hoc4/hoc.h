typedef struct Symbol { /* entrada de la tabla de s�mbolos */
	char   *name;
	short   type;   /* VAR, BLTIN, UNDEF */
	union {
		double val;	       /* si es VAR */
		double  (*ptr)(double);      /* s� es BLTIN */
	} u;
	struct Symbol   *next;  /* para ligarse a otro */ 
} Symbol;

Symbol *install(char *s,int t, double d), *lookup(char *s);

typedef union Datum {   /* tipo de la pila del int�rprete */
   double  val;
   Symbol  *sym; 
} Datum; 

extern Datum pop();
typedef void (*Inst)(void);  /* instrucci�n de m�quina */ 

#define STOP    (Inst) 0
extern	Inst prog[];
extern	void eval();
extern	void add();
extern	void sub(); 
extern	void mul(); 
extern	void div(); 
extern	void negate(); 
extern	void power();
extern	void assign(); 
extern	void bltin(); 
extern	void varpush(); 
extern	void constpush();
extern	void print();
extern	void pop1();
