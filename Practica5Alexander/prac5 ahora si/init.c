#include "hoc.h"
#include "y.tab.h"
#include <math.h>

// NUEVO: Funciones BLTIN complejas
Complejo c_log(Complejo c) { 
    // log(a+bi) = log(r) + i*theta
    double r = sqrt(c.real*c.real + c.imag*c.imag);
    double theta = atan2(c.imag, c.real);
    if (r == 0.0) execerror("log(0)", (char*)0);
    return (Complejo){log(r), theta}; 
}
Complejo c_sqrt(Complejo c) {
    // sqrt(r(cos(t) + i*sin(t))) = r^0.5 * (cos(t/2) + i*sin(t/2))
    double r = sqrt(c.real*c.real + c.imag*c.imag);
    double theta = atan2(c.imag, c.real);
    return (Complejo){sqrt(r) * cos(theta/2.0), sqrt(r) * sin(theta/2.0)};
}
Complejo c_exp(Complejo c) {
    // exp(a+bi) = exp(a) * (cos(b) + i*sin(b))
    double exp_a = exp(c.real);
    return (Complejo){exp_a * cos(c.imag), exp_a * sin(c.imag)};
}
Complejo c_sin(Complejo c) {
    // sin(a+bi) = sin(a)cosh(b) + i*cos(a)sinh(b)
    return (Complejo){sin(c.real)*cosh(c.imag), cos(c.real)*sinh(c.imag)};
}
Complejo c_cos(Complejo c) {
    // cos(a+bi) = cos(a)cosh(b) - i*sin(a)sinh(b)
    return (Complejo){cos(c.real)*cosh(c.imag), -sin(c.real)*sinh(c.imag)};
}
Complejo c_atan(Complejo c) {
    // (Simplificado: solo atan(real))
    if (c.imag != 0.0) execerror("atan(complex) not supported", (char*)0);
    return (Complejo){atan(c.real), 0.0};
}
Complejo c_log10(Complejo c) {
    // log10(z) = log(z) / log(10)
    Complejo log_z = c_log(c);
    double log_10 = log(10.0);
    return (Complejo){log_z.real / log_10, log_z.imag / log_10};
}
Complejo c_integer(Complejo c) {
    return (Complejo){(double)(long)c.real, (double)(long)c.imag};
}
Complejo c_abs(Complejo c) {
    // Devuelve la magnitud (módulo) como un complejo (real, 0)
    double mag = sqrt(c.real*c.real + c.imag*c.imag);
    return (Complejo){mag, 0.0};
}


static struct { char   *name;	/* Palabras clave */
int    kval;
} keywords[] = {
"if",		IF,
"else" ,	ELSE,
"while",	WHILE,
"print",	PRINT,
0,      0,
};
static struct {         /* Constantes */ 
    char *name; 
    Complejo cval; // MODIFICADO
} consts[] = {
// MODIFICADO: Constantes como complejos (real, 0)
"PI",    (Complejo){3.14159265358979323846, 0.0},
"E",     (Complejo){2.71828182845904523536, 0.0},
"GAMMA", (Complejo){0.57721566490153286060, 0.0},  /* Euler */
"DEG",   (Complejo){57.29577951308232087680, 0.0},  /* grado/radian */
"PHI",   (Complejo){1.6180339887498948*820, 0.0},  /* proporcion dorada */
"I",     (Complejo){0.0, 1.0},
// NUEVO: Añadida 'i' minúscula como constante
"i",     (Complejo){0.0, 1.0},
0,       (Complejo){0.0, 0.0} // MODIFICADO
};

static struct {	/*	Predefinidos */
char *name;
Complejo	(*func)(Complejo); // MODIFICADO
} builtins[] =	{
// MODIFICADO: Usar funciones complejas
"sin",	c_sin,
"cos" ,	c_cos, // "coa" era un typo en el original
"atan",	c_atan,
"log", c_log,
"log10", c_log10,
"exp", c_exp,
"sqrt",	c_sqrt,
"int" ,	c_integer,
"abs",	c_abs, // 'abs' ahora devuelve (mag, 0)
0,	0
};

// MODIFICADO: Añadido 'void'
void init(void)  /* instalar constantes y predefinidos en la tabla */
{
int i;
Symbol *s;
Complejo d_zero = {0.0, 0.0}; // MODIFICADO

for (i = 0; keywords[i].name; i++)
	// MODIFICADO: Pasa d_zero
	install(keywords[i].name, keywords[i].kval, d_zero);
for (i = 0; consts[i].name; i++)
	// MODIFICADO: Pasa cval (Complejo)
	install(consts[i].name, VAR, consts[i].cval);
for (i = 0; builtins[i].name; i++) {
	// MODIFICADO: Pasa d_zero
	s = install(builtins[i].name, BLTIN, d_zero); 
	s->u.ptr = builtins[i].func; // MODIFICADO
}
}
