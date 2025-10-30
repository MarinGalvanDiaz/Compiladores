#include <math.h> 
#include <errno.h>
#include "hoc.h"     // NUEVO
#include "y.tab.h" // NUEVO

extern  int errno;
/* double  errcheck(); // Prototipo ahora en hoc.h */

/*
double Log(x) // Prototipo ahora en hoc.h
double x;
{
return errcheck(log(x) , "log");
}
*/

double Log(double x) {
    return errcheck(log(x), "log");
}


double Log10(double x)
{
return  errcheck(log10(x), "log10");
}

double Sqrt(double x) 
{
return errcheck(sqrt(x), "sqrt"); 
}

double Exp(double x)
{
return errcheck( exp(x) , "exp" ) ;
}

double Pow(double x, double y)
{
return errcheck(pow(x,y), "exponentiation");
}

double integer(double x)
{
return (double)(long)x;
}
double errcheck(double d, char *s)   /* comprobar resultado de llamada a biblioteca */ 
{
   if (errno == EDOM) { 
     errno = 0;
     execerror(s, "argument out of domain"); 
   } else if (errno == ERANGE) 
   { errno = 0;
     execerror(s, "result out of range"); 
   } 
   return d;
}
