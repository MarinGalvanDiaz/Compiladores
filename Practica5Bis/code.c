#include <stdio.h>
#include <math.h>
#include "hoc.h"
#include "vector.h"

#define NSTACK  256
Datum stack[NSTACK];
Datum *stackp;

void execerror(char *s, char *t);  // Declarar execerror

void push(Datum d)   /* meter d a la pila */
{
    if (stackp >= &stack[NSTACK]) {
        execerror("stack overflow", (char *) 0);
    }
    *stackp++ = d;
}

Datum pop()     /* sacar y retornar de la pila el elemento del tope */
{
    if (stackp <= stack) {
        execerror("stack underflow", (char *) 0);
    }
    return *--stackp;
}

void eval()     /* evaluar variable en el tope de la pila */
{
    Datum d;
    d = pop();
    if (d.sym->type == HOC_UNDEF) {  // Usar HOC_UNDEF
        execerror("undefined variable", d.sym->name);
    }
    d.val = d.sym->u.val;
    push(d);
}

void add()      /* sumar los dos valores del tope de la pila */
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val += d2.val;
    push(d1);
}

void sub()      /* restar los dos valores del tope de la pila */
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val -= d2.val;
    push(d1);
}

void mul()      /* multiplicar los dos valores del tope de la pila */
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val *= d2.val;
    push(d1);
}

void divide()   /* dividir los dos valores del tope de la pila */
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    if (d2.val == 0.0) {
        execerror("division by zero", "");
    }
    d1.val /= d2.val;
    push(d1);
}

void negate()   /* negar el valor del tope de la pila */
{
    Datum d;
    d = pop();
    d.val = -d.val;
    push(d);
}

void power()    /* elevar a potencia */
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = pow(d1.val, d2.val);
    push(d1);
}

void assign()   /* asignar valor a variable */
{
    Datum d = pop();  // valor a asignar
    Symbol *s = pop().sym;
    
    // Verificar si estamos asignando un vector
    if (temp_vector_size > 0) {
        assign_vector_to_var(s, temp_vector_data, temp_vector_size);
        temp_vector_size = 0; // reset
    } else {
        // Asignación normal de variable escalar
        s->u.val = d.val;
    }
}

void bltin()    /* llamar a función predefinida */
{
    Datum d;
    d = pop();
    d.val = (*(double (*)(double)) *progp++)(d.val);
    push(d);
}

void varpush()  /* empujar variable a la pila */
{
    Datum d;
    d.sym = (Symbol *) *progp++;
    push(d);
}

void constpush() /* empujar constante a la pila */
{
    Datum d;
    d.val = ((Symbol *) *progp++)->u.val;
    push(d);
}

void print()    /* imprimir valor de expresión */
{
    Datum d;
    d = pop();
    printf("\t%.8g\n", d.val);
}

void prexpr()   /* imprimir valor de expresión sin newline */
{
    Datum d;
    d = pop();
    printf("%.8g ", d.val);
}

void pop1()     /* descartar valor del tope de la pila */
{
    pop();
}

// Funciones de comparación
void gt() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val > d2.val); push(d1); }
void lt() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val < d2.val); push(d1); }
void eq() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val == d2.val); push(d1); }
void ge() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val >= d2.val); push(d1); }
void le() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val <= d2.val); push(d1); }
void ne() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val != d2.val); push(d1); }
void and() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val != 0.0 && d2.val != 0.0); push(d1); }
void or() { Datum d2 = pop(), d1 = pop(); d1.val = (double)(d1.val != 0.0 || d2.val != 0.0); push(d1); }
void not() { Datum d = pop(); d.val = (double)(d.val == 0.0); push(d); }

void ifcode()   /* instrucción if */
{
    Inst *savepc = progp;
    progp += 3;
    execute(savepc);
}

void whilecode() /* instrucción while */
{
    Inst *savepc = progp;
    progp += 3;
    execute(savepc);
}

void initcode()  /* inicializar generador de código */
{
    progp = prog;
}

Inst *code(Inst f)  /* generar una instrucción */
{
    Inst *oprogp = progp;
    if (progp >= &prog[NPROG]) {
        execerror("program too big", (char *) 0);
    }
    *progp++ = f;
    return oprogp;
}

void execute(Inst *p)  /* ejecutar el programa */
{
    for (; *p != STOP; ) {
        (*((Inst *) (*p)))();
        p++;
    }
}

// Inicializar la pila
void initstack()
{
    stackp = stack;
}