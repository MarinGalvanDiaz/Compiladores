#include "hoc.h" 
#include "y.tab.h"
#include <math.h> // Necesario para fabs y pow
#include <stdio.h> // Para printf

#define NSTACK  256
static  Datum  stack[NSTACK];  /* la pila */
static  Datum   *stackp;       /* siguiente lugar libre en la pila */
#define NPROG   2000
Inst    prog[NPROG];    /* la máquina */
Inst    *progp;         /* siguiente lugar libre para la generación de código */
Inst    *pc;	/* contador de programa durante la ejecución */

void initcode()      /* inicialización para la generación de código */ {
   stackp = stack;
   progp = prog;
}

void push(Datum d){	/* meter d en la pila  */
if (stackp >= &stack[NSTACK])
execerror("stack overflow", (char *) 0);
*stackp++ = d;
}

void pop1( ){     /* sacar y retornar de la pila el elemento del tope */
   if (stackp <= stack)
      execerror("stack underflow", (char *) 0);
   --stackp;
}

Datum pop( )     /* sacar y retornar de la pila el elemento del tope */
{
if (stackp <= stack)
execerror("stack underflow", (char *) 0);
return  *--stackp;
}


void constpush( )	/* meter una constante a la pila  */
{
Datum d;
// (Ahora funciona con Complejo gracias a hoc.h y symbol.c)
d.val  =  ((Symbol  *)*pc++)->u.val;
push(d);
}

void varpush()	/* meter una variable a la pila   */
{
Datum d;
d.sym  =  (Symbol   *)(*pc++);
push(d);
}

void 
whilecode() {
   Datum d;
   Inst  *savepc  = pc;	/* cuerpo de la iteración  */
   execute(savepc+2);     /* cond  */ 
   d  =  pop(); 
   // MODIFICADO: Usar dval para la condición
   while   (d.dval)   {
      execute(*((Inst  **)(savepc)));     /* body */
      execute(savepc+2);/*finish*/
      d  = pop(); 
   } 
   pc  =  *((Inst  **)(savepc+1));     /* siguiente proposición   */
}
void ifcode(){
   Datum d;
   Inst  *savepc  = pc;	/* parte then */
   execute(savepc+3);	/* condición   */
   d  =  pop(); 
   // MODIFICADO: Usar dval para la condición
   if (d.dval)
      execute(*((Inst   **)(savepc))); 
   else  if   (*((Inst  **)(savepc+1)))   /* ¿parte else?   */
      execute(*(( Inst  **) (savepc+1)));
   pc  =  *((Inst  **)(savepc+2));	/* siguiente proposición   */ 
}

void eval( )	/* evaluar una variable en la pila   */
{
Datum  d;
d   =  pop();
// MODIFICADO: Usar INDEF
if   (d.sym->type   ==   INDEF)
execerror("undefined variable",   
d.sym->name); 
// MODIFICADO: Asigna el complejo
d.val   =  d.sym->u.val; 
push(d);
}

void add( )	/* sumar los dos elementos superiores de la pila   */
{
Datum d1,   d2; 
d2  =  pop(); 
d1   =  pop(); 
// MODIFICADO: Suma compleja
d1.val.real += d2.val.real;
d1.val.imag += d2.val.imag;
push(d1); 
}

void sub(){
Datum d1,  d2; 
d2  = pop(); 
d1  = pop(); 
// MODIFICADO: Resta compleja
d1.val.real -= d2.val.real;
d1.val.imag -= d2.val.imag;
push(d1);
}
void mul(){
Datum d1, d2;
double r;
d2 = pop(); 
d1 = pop(); 
// MODIFICADO: Multiplicación compleja (a+bi)*(c+di) = (ac-bd) + (ad+bc)i
r = d1.val.real * d2.val.real - d1.val.imag * d2.val.imag;
d1.val.imag = d1.val.real * d2.val.imag + d1.val.imag * d2.val.real;
d1.val.real = r;
push(d1);
}

// MODIFICADO: Renombrada a 'c_div'
void c_div( ){
Datum d1, d2;
double r, den;
d2 = pop();
// MODIFICADO: División compleja
den = d2.val.real * d2.val.real + d2.val.imag * d2.val.imag;
if (den == 0.0)
execerror("division by zero", (char *)0);
d1 = pop(); 
r = (d1.val.real * d2.val.real + d1.val.imag * d2.val.imag) / den;
d1.val.imag = (d1.val.imag * d2.val.real - d1.val.real * d2.val.imag) / den;
d1.val.real = r;
push(d1);
}
void negate(){
Datum d; 
d = pop(); 
// MODIFICADO: Negación compleja
d.val.real  =  -d.val.real; 
d.val.imag  =  -d.val.imag; 
push(d);
}
void power(){
// Nota: Solo soporta (Complejo ^ double) o (double ^ double)
Datum d1, d2;
/* extern double Pow(); */ // Prototipo ahora en hoc.h
d2 = pop(); // Exponente
d1 = pop(); // Base

if (d2.val.imag != 0.0) {
    execerror("complex exponent not supported in power", (char *)0);
}

if (d1.val.imag == 0.0) { // Base real
    d1.val.real = Pow(d1.val.real, d2.val.real);
    // d1.val.imag sigue siendo 0.0
} else {
    // Potencia de complejo a real (De Moivre)
    double r = sqrt(d1.val.real * d1.val.real + d1.val.imag * d1.val.imag);
    double theta = atan2(d1.val.imag, d1.val.real);
    double n = d2.val.real;
    double rn = pow(r, n);
    d1.val.real = rn * cos(n * theta);
    d1.val.imag = rn * sin(n * theta);
}
push(d1);
}

void assign( )        /* asignar el valor superior al siguientevalor */ 
{
Datum d1, d2;
d1 = pop(); // Símbolo (destino)
d2 = pop(); // Valor (origen)
// MODIFICADO: Usar INDEF
if (d1.sym->type != VAR && d1.sym->type != INDEF) 
execerror("assignment to non-variable", d1.sym->name);
// MODIFICADO: Asigna el complejo
d1.sym->u.val = d2.val;
d1.sym->type = VAR;
push(d2); 
} 

// MODIFICADO: Cambiado el formato de impresión
void prexpr() {      
   Datum d;
d = pop();
// MODIFICADO: Imprimir en formato "real + imagi"
   printf("%.8g", d.val.real);
   if (d.val.imag > 0) {
       printf(" + %.8gi", d.val.imag);
   } else if (d.val.imag < 0) {
       printf(" %.8gi", d.val.imag); // El negativo ya viene con %.8g
   }
   // MODIFICADO: Cambiado espacio por salto de línea
   printf("\n"); 
}

// MODIFICADO: Cambiado el formato de impresión
void print( ){  /* sacar el valor superior de la pila e imprimirlo */ 
 Datum d;
 d = pop();
 // MODIFICADO: Imprimir en formato "real + imagi"
   printf("\t"); // Añade el tabulador que tenía antes
   printf("%.8g", d.val.real);
   if (d.val.imag > 0) {
       printf(" + %.8gi", d.val.imag);
   } else if (d.val.imag < 0) {
       printf(" %.8gi", d.val.imag);
   }
   printf("\n"); // Añade el newline que tenía antes
}

void bltin( )/* evaluar un predefinido en el tope de la pila  */
{
Datum d;
d  =  pop();
// MODIFICADO: Manejar (Complejo (*)(Complejo))
// El puntero a función se guarda en prog[] (un array de Inst, o void (*)(void))
// Se recupera *pc++ y se castea al tipo de función correcto.
d.val  =   (  *(Complejo   (*)(Complejo))(*pc++)  ) (d.val);
push(d);
}
Inst *code(Inst f){ /* instalar una instrucción u operando   */
   //puts("code1");
   Inst *oprogp = progp;
   if (progp > &prog [ NPROG -1 ])
     execerror("program too big", (char *) 0);
   *progp++ = f;
   return oprogp;
}
void execute(Inst *p){	/* ejecución con la máquina   */
for  (pc  =  p;   *pc != STOP; ) 
	(*pc++)();
}

// NUEVO: Helper para magnitud
double c_abs_val(Complejo c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}

void gt() {
Datum d1,  d2;
d2 = pop();
d1 = pop();
// MODIFICADO: Compara magnitud, guarda en dval
d1.dval  =   (double)(c_abs_val(d1.val)  > c_abs_val(d2.val));
push(d1);
}

void lt(){
Datum d1,  d2;
d2 = pop();
d1 = pop();
// MODIFICADO: Compara magnitud, guarda en dval
d1.dval  =   (double)(c_abs_val(d1.val)  < c_abs_val(d2.val));
push(d1);
}

void ge( ) {
Datum d1,  d2;
d2  = pop();
d1  = pop();
// MODIFICADO: Compara magnitud, guarda en dval
d1.dval   =   (double)(c_abs_val(d1.val)  >= c_abs_val(d2.val));
push(d1) ;
}

void le() {
Datum d1,  d2;
d2   =  pop();
d1   =  pop();
// MODIFICADO: Compara magnitud, guarda en dval
d1.dval  =   (double)(c_abs_val(d1.val)   <=  c_abs_val(d2.val));
push(d1);
}

void eq( ) {
Datum d1,  d2;
d2  = pop();
d1  = pop();
// MODIFICADO: Compara igualdad exacta (real y imag), guarda en dval
d1.dval  =   (double) (d1.val.real  ==  d2.val.real && d1.val.imag == d2.val.imag);
push(d1);
}

void ne(){
Datum d1, d2;
d2 = pop();
d1 = pop();
// MODIFICADO: Compara desigualdad, guarda en dval
d1.dval = (double)(d1.val.real != d2.val.real || d1.val.imag != d2.val.imag);
push(d1);
}

void and(){
Datum d1,   d2;
d2   = pop();
d1   = pop();
// MODIFICADO: Opera sobre dval
d1.dval = (double)(d1.dval   !=   0.0 && d2.dval   !=  0.0);
push(d1);
}

void or()
{
Datum d1, d2;
d2 = pop();
d1 = pop();
// MODIFICADO: Corregido de d2.val a d2.dval
d1.dval = (double)(d1.dval != 0.0 || d2.dval != 0.0);
push(d1);
}

void not( )
{
Datum d;
d = pop();
// MODIFICADO: Opera sobre dval
d.dval = (double)(d.dval == 0.0);
push(d);
}
