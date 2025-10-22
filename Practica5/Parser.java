//### This file created by BYACC 1.8(/Java extension  1.15)
//### Java capabilities added 7 Jan 97, Bob Jamison
//### Updated : 27 Nov 97  -- Bob Jamison, Joe Nieten
//###           01 Jan 98  -- Bob Jamison -- fixed generic semantic constructor
//###           01 Jun 99  -- Bob Jamison -- added Runnable support
//###           06 Aug 00  -- Bob Jamison -- made state variables class-global
//###           03 Jan 01  -- Bob Jamison -- improved flags, tracing
//###           16 May 01  -- Bob Jamison -- added custom stack sizing
//###           04 Mar 02  -- Yuval Oren  -- improved java performance, added options
//###           14 Mar 02  -- Tomas Hurka -- -d support, static initializer workaround
//### Please send bug reports to tom@hukatronic.cz
//### static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";






//#line 2 "P5.y"
	import java.lang.Math;
	import java.io.*;
	import java.util.StringTokenizer;
//#line 21 "Parser.java"




public class Parser
{

boolean yydebug;        //do I want debug output?
int yynerrs;            //number of errors so far
int yyerrflag;          //was there an error?
int yychar;             //the current working character

//########## MESSAGES ##########
//###############################################################
// method: debug
//###############################################################
void debug(String msg)
{
  if (yydebug)
    System.out.println(msg);
}

//########## STATE STACK ##########
final static int YYSTACKSIZE = 500;  //maximum stack size
int statestk[] = new int[YYSTACKSIZE]; //state stack
int stateptr;
int stateptrmax;                     //highest index of stackptr
int statemax;                        //state when highest index reached
//###############################################################
// methods: state stack push,pop,drop,peek
//###############################################################
final void state_push(int state)
{
  try {
		stateptr++;
		statestk[stateptr]=state;
	 }
	 catch (ArrayIndexOutOfBoundsException e) {
     int oldsize = statestk.length;
     int newsize = oldsize * 2;
     int[] newstack = new int[newsize];
     System.arraycopy(statestk,0,newstack,0,oldsize);
     statestk = newstack;
     statestk[stateptr]=state;
  }
}
final int state_pop()
{
  return statestk[stateptr--];
}
final void state_drop(int cnt)
{
  stateptr -= cnt; 
}
final int state_peek(int relative)
{
  return statestk[stateptr-relative];
}
//###############################################################
// method: init_stacks : allocate and prepare stacks
//###############################################################
final boolean init_stacks()
{
  stateptr = -1;
  val_init();
  return true;
}
//###############################################################
// method: dump_stacks : show n levels of the stacks
//###############################################################
void dump_stacks(int count)
{
int i;
  System.out.println("=index==state====value=     s:"+stateptr+"  v:"+valptr);
  for (i=0;i<count;i++)
    System.out.println(" "+i+"    "+statestk[i]+"      "+valstk[i]);
  System.out.println("======================");
}


//########## SEMANTIC VALUES ##########
//public class ParserVal is defined in ParserVal.java


String   yytext;//user variable to return contextual strings
ParserVal yyval; //used to return semantic vals from action routines
ParserVal yylval;//the 'lval' (result) I got from yylex()
ParserVal valstk[];
int valptr;
//###############################################################
// methods: value stack push,pop,drop,peek.
//###############################################################
void val_init()
{
  valstk=new ParserVal[YYSTACKSIZE];
  yyval=new ParserVal();
  yylval=new ParserVal();
  valptr=-1;
}
void val_push(ParserVal val)
{
  if (valptr>=YYSTACKSIZE)
    return;
  valstk[++valptr]=val;
}
ParserVal val_pop()
{
  if (valptr<0)
    return new ParserVal();
  return valstk[valptr--];
}
void val_drop(int cnt)
{
int ptr;
  ptr=valptr-cnt;
  if (ptr<0)
    return;
  valptr = ptr;
}
ParserVal val_peek(int relative)
{
int ptr;
  ptr=valptr-relative;
  if (ptr<0)
    return new ParserVal();
  return valstk[ptr];
}
final ParserVal dup_yyval(ParserVal val)
{
  ParserVal dup = new ParserVal();
  dup.ival = val.ival;
  dup.dval = val.dval;
  dup.sval = val.sval;
  dup.obj = val.obj;
  return dup;
}
//#### end semantic value section ####
public final static short IF=257;
public final static short ELSE=258;
public final static short WHILE=259;
public final static short FOR=260;
public final static short COMP=261;
public final static short DIFERENTES=262;
public final static short MAY=263;
public final static short MEN=264;
public final static short MAYI=265;
public final static short MENI=266;
public final static short FNCT=267;
public final static short NUMBER=268;
public final static short VAR=269;
public final static short AND=270;
public final static short OR=271;
public final static short YYERRCODE=256;
final static short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    4,    3,
    5,    6,    7,    7,    7,
};
final static short yylen[] = {                            2,
    0,    2,    3,    2,    3,    1,    1,    7,    3,    4,
    3,    3,    3,    3,    3,   14,   10,   10,   16,    3,
    3,    3,    3,    3,    3,    3,    3,    2,    0,    1,
    1,    1,    0,    1,    3,
};
final static short yydefred[] = {                         1,
    0,   30,   31,   32,    0,    7,    0,    0,    2,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    4,    0,    0,    0,    0,
    0,    0,   15,    5,    0,    0,    0,    0,    0,    0,
    0,   27,    0,    0,    0,    0,    0,    0,    0,    0,
   10,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    8,    0,    0,    0,    0,
    0,    0,    0,   29,    0,    0,   17,   18,    0,    0,
    0,    0,    0,    0,    0,   16,    0,   29,   19,
};
final static short yydgoto[] = {                          1,
   12,   13,   14,   63,   15,   16,   60,
};
final static short yysindex[] = {                         0,
  -10,    0,    0,    0,  -88,    0,  -56,  -32,    0,  -32,
  -32,   -6,   56,  -28,  -24,  -14,  -32,  -32, -233,   67,
   34,    0,   78,  -32,  -32,  -32,  -32,  -32,  -32,  -32,
  -32,  -32,  -32,  -32,  -32,    0,  -32,  -32,  -32,   89,
  122,  -32,    0,    0,  285,  -85,  -69, -210, -164, -233,
 -236,    0,  135,  135,  264,  264,  122,  122,  122,    6,
    0,  100,   31,   32,  -32,   15,  -32,  -45,  -43,  122,
  -32,  111,  -32,  -32,  122,    0,  -32,  -32,   24,  -31,
  -20,  -32, -174,    0,    6,  -15,    0,    0,   52,  -32,
   -9,  -32,  -32,  -12,  -32,    0,   -7,    0,    0,
};
final static short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    3,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -23,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -42,    0,
  -35,    0,    0,    0,  402,  397,  376,  366,  371,  189,
   45,    0,  -30,   10,   -2,  430,   54,   54,  -34,   60,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   81,
    0,    0,    0,    0,   60,    0,   -1,   -1,    0,    0,
    0,  -13,   23,    0,   54,    0,    0,    0,    0,    0,
    0,   -1,    0,    0,   -1,    0,    0,    0,    0,
};
final static short yygindex[] = {                         0,
  -41,  475,    0,  115,    0,    0,   44,
};
final static int YYTABLESIZE=663;
static short yytable[];
static { yytable();}
static void yytable(){
yytable = new short[]{                          9,
    8,   33,   17,   22,   18,    9,   34,   11,    9,   34,
   13,   37,   13,   13,   13,   38,   33,   28,   28,   28,
   28,   28,    8,    9,   34,   39,    8,   33,   13,   11,
   33,   77,   78,   11,   31,   28,   30,   31,   11,   11,
   11,   11,   11,    6,    6,    6,    6,    6,   92,   65,
   14,   95,   14,   14,   14,   29,   11,    9,   10,   30,
   31,    6,   13,   29,   29,   29,   29,   29,   14,   28,
   28,   68,   69,   71,   43,   34,   32,   73,   33,   74,
   10,   29,   82,   86,   10,   26,   26,   26,   26,   26,
   11,   11,   91,   83,   29,    6,    6,   34,   32,   27,
   33,   29,   14,   26,   84,   30,   31,   90,   34,   32,
   42,   33,   96,   93,   36,   29,   29,   98,   29,   34,
   32,   35,   33,   29,   35,   85,    0,   35,    0,    0,
   34,   32,    0,   33,    0,    0,   44,   26,   26,   35,
    0,   34,   32,   67,   33,    0,    0,    0,    0,   35,
    0,    0,   34,   32,    0,   33,    0,    0,    0,    0,
   35,    0,    0,   34,   32,    0,   33,    0,    0,    0,
    0,   35,   64,    0,   66,    0,   34,   26,   27,   28,
   29,   61,   35,    0,   30,   31,    0,    0,    0,   79,
    0,   80,   81,   35,   27,   28,   29,   87,   88,   89,
   30,   31,    0,   76,   35,    0,   94,    0,    0,   97,
    0,    0,   99,    0,    0,   35,    0,    0,    0,    0,
    0,    0,    0,    0,    2,    0,    3,    4,   35,   23,
   23,   23,   23,   23,    5,    6,    7,   28,   28,   28,
   28,   28,   28,    0,    0,    0,    2,   23,    3,    4,
    2,    0,    3,    4,    0,    0,    5,    6,    7,    0,
    5,    6,    7,    6,    6,    6,    6,    6,    6,    0,
    0,    0,    6,    6,    0,    0,    0,    0,    0,    0,
    0,   23,   23,   29,   29,   29,   29,   29,   29,    0,
    0,    0,   29,   29,   24,   25,   26,   27,   28,   29,
    0,    0,    0,   30,   31,   26,   26,   26,   26,   26,
   26,    0,    0,    0,   26,    0,   24,   25,   26,   27,
   28,   29,    0,    0,    0,   30,   31,   24,   25,   26,
   27,   28,   29,    0,    0,    0,   30,   31,   24,   25,
   26,   27,   28,   29,    0,    0,    0,   30,   31,   24,
   25,   26,   27,   28,   29,    0,    0,    0,   30,   31,
   24,   25,   26,   27,   28,   29,    0,    0,    0,   30,
   31,   24,   25,   26,   27,   28,   29,    0,    0,    0,
   30,   31,   24,   25,   26,   27,   28,   29,    0,    0,
    0,   30,   31,    0,    0,   24,   25,   26,   27,   28,
   29,    0,    0,    0,   30,   31,   22,   22,   22,   22,
   22,   25,   25,   25,   25,   25,   24,   24,   24,   24,
   24,    0,    0,    0,   22,    0,    0,    0,    0,   25,
    0,    0,    0,    0,   24,    0,    0,   21,   21,   21,
   21,   21,   20,   20,   20,   20,   20,    0,    0,   23,
   23,   23,   23,   23,   23,   21,    0,    0,   22,   22,
   20,    0,    0,   25,   25,    0,    0,    0,   24,   24,
   12,   12,   12,   12,   12,    0,    0,    0,    0,    0,
    0,    0,   19,    0,   20,   21,   23,    0,   12,   21,
   21,   40,   41,    0,   20,   20,    0,    0,   45,   46,
   47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
    0,   57,   58,   59,    0,    0,   62,    0,    0,    0,
    0,    0,   12,   12,   24,   25,   26,   27,   28,   29,
    0,    0,    0,   30,   31,    0,    0,    0,    0,   70,
    0,   72,    0,    0,    0,   75,   25,   26,   27,   28,
   29,   23,   23,    0,   30,   31,   59,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   23,    0,    0,   23,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   22,   22,   22,   22,
   22,   25,   25,   25,    0,   25,   24,   24,   24,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   21,   21,    0,
    0,    0,   20,
};
}
static short yycheck[];
static { yycheck(); }
static void yycheck() {
yycheck = new short[] {                         10,
   33,   44,   91,   10,   61,   41,   41,   40,   44,   44,
   41,   40,   43,   44,   45,   40,   59,   41,   42,   43,
   44,   45,   33,   59,   59,   40,   33,   41,   59,   40,
   44,   73,   74,   40,  271,   59,  270,  271,   41,   42,
   43,   44,   45,   41,   42,   43,   44,   45,   90,   44,
   41,   93,   43,   44,   45,  266,   59,   93,   91,  270,
  271,   59,   93,   41,   42,   43,   44,   45,   59,   93,
   94,   41,   41,   59,   41,   42,   43,  123,   45,  123,
   91,   59,   59,  258,   91,   41,   42,   43,   44,   45,
   93,   94,   41,  125,   41,   93,   94,   42,   43,  264,
   45,  266,   93,   59,  125,  270,  271,  123,   42,   43,
   44,   45,  125,  123,   59,   93,   94,  125,   59,   42,
   43,   41,   45,  125,   44,   82,   -1,   94,   -1,   -1,
   42,   43,   -1,   45,   -1,   -1,   59,   93,   94,   59,
   -1,   42,   43,   44,   45,   -1,   -1,   -1,   -1,   94,
   -1,   -1,   42,   43,   -1,   45,   -1,   -1,   -1,   -1,
   94,   -1,   -1,   42,   43,   -1,   45,   -1,   -1,   -1,
   -1,   94,   58,   -1,   60,   -1,   42,  263,  264,  265,
  266,   93,   94,   -1,  270,  271,   -1,   -1,   -1,   75,
   -1,   77,   78,   94,  264,  265,  266,   83,   84,   85,
  270,  271,   -1,   93,   94,   -1,   92,   -1,   -1,   95,
   -1,   -1,   98,   -1,   -1,   94,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  257,   -1,  259,  260,   94,   41,
   42,   43,   44,   45,  267,  268,  269,  261,  262,  263,
  264,  265,  266,   -1,   -1,   -1,  257,   59,  259,  260,
  257,   -1,  259,  260,   -1,   -1,  267,  268,  269,   -1,
  267,  268,  269,  261,  262,  263,  264,  265,  266,   -1,
   -1,   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   93,   94,  261,  262,  263,  264,  265,  266,   -1,
   -1,   -1,  270,  271,  261,  262,  263,  264,  265,  266,
   -1,   -1,   -1,  270,  271,  261,  262,  263,  264,  265,
  266,   -1,   -1,   -1,  270,   -1,  261,  262,  263,  264,
  265,  266,   -1,   -1,   -1,  270,  271,  261,  262,  263,
  264,  265,  266,   -1,   -1,   -1,  270,  271,  261,  262,
  263,  264,  265,  266,   -1,   -1,   -1,  270,  271,  261,
  262,  263,  264,  265,  266,   -1,   -1,   -1,  270,  271,
  261,  262,  263,  264,  265,  266,   -1,   -1,   -1,  270,
  271,  261,  262,  263,  264,  265,  266,   -1,   -1,   -1,
  270,  271,  261,  262,  263,  264,  265,  266,   -1,   -1,
   -1,  270,  271,   -1,   -1,  261,  262,  263,  264,  265,
  266,   -1,   -1,   -1,  270,  271,   41,   42,   43,   44,
   45,   41,   42,   43,   44,   45,   41,   42,   43,   44,
   45,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,   59,
   -1,   -1,   -1,   -1,   59,   -1,   -1,   41,   42,   43,
   44,   45,   41,   42,   43,   44,   45,   -1,   -1,  261,
  262,  263,  264,  265,  266,   59,   -1,   -1,   93,   94,
   59,   -1,   -1,   93,   94,   -1,   -1,   -1,   93,   94,
   41,   42,   43,   44,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,    8,   -1,   10,   11,   12,   -1,   59,   93,
   94,   17,   18,   -1,   93,   94,   -1,   -1,   24,   25,
   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
   -1,   37,   38,   39,   -1,   -1,   42,   -1,   -1,   -1,
   -1,   -1,   93,   94,  261,  262,  263,  264,  265,  266,
   -1,   -1,   -1,  270,  271,   -1,   -1,   -1,   -1,   65,
   -1,   67,   -1,   -1,   -1,   71,  262,  263,  264,  265,
  266,   77,   78,   -1,  270,  271,   82,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   92,   -1,   -1,   95,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  261,  262,  263,  264,
  265,  261,  262,  263,   -1,  265,  261,  262,  263,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  261,  262,   -1,
   -1,   -1,  261,
};
}
final static short YYFINAL=1;
final static short YYMAXTOKEN=271;
final static String yyname[] = {
"end-of-file",null,null,null,null,null,null,null,null,null,"'\\n'",null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,"'!'",null,null,null,null,null,null,"'('","')'","'*'","'+'",
"','","'-'",null,null,null,null,null,null,null,null,null,null,null,null,null,
"';'",null,"'='",null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,"'['",null,"']'","'^'",null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,"'{'",null,"'}'",null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,"IF","ELSE","WHILE","FOR","COMP",
"DIFERENTES","MAY","MEN","MAYI","MENI","FNCT","NUMBER","VAR","AND","OR",
};
final static String yyrule[] = {
"$accept : list",
"list :",
"list : list '\\n'",
"list : list linea '\\n'",
"linea : exp ';'",
"linea : linea exp ';'",
"exp : VAR",
"exp : NUMBER",
"exp : '[' exp ',' exp ',' exp ']'",
"exp : VAR '=' exp",
"exp : FNCT '[' exp ']'",
"exp : exp '*' exp",
"exp : exp '^' exp",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : '(' exp ')'",
"exp : if_ '(' exp stop_ ')' '{' linea stop_ '}' ELSE '{' linea stop_ '}'",
"exp : if_ '(' exp stop_ ')' '{' linea stop_ '}' stop_",
"exp : while_ '(' exp stop_ ')' '{' linea stop_ '}' stop_",
"exp : for_ '(' instrucciones stop_ ';' exp stop_ ';' instrucciones stop_ ')' '{' linea stop_ '}' stop_",
"exp : exp COMP exp",
"exp : exp DIFERENTES exp",
"exp : exp MEN exp",
"exp : exp MENI exp",
"exp : exp MAY exp",
"exp : exp MAYI exp",
"exp : exp AND exp",
"exp : exp OR exp",
"exp : '!' exp",
"stop_ :",
"if_ : IF",
"while_ : WHILE",
"for_ : FOR",
"instrucciones :",
"instrucciones : exp",
"instrucciones : instrucciones ',' exp",
};

//#line 186 "P5.y"



TablaDeSimbolos tablaDeSimbolos = new TablaDeSimbolos();
MaquinaDePila maquina = new MaquinaDePila(tablaDeSimbolos);
int i = 0;
int j = 0;
double[][] auxiliar; 

Funcion funcionAux;
boolean huboError;

String ins;
StringTokenizer st;

void yyerror(String s){
	huboError = true;
	System.out.println("error:"+s);
}

boolean newline;
int yylex(){
	String s;
int tok = 0;
	Double d;
	if (!st.hasMoreTokens()){
		if (!newline){
			newline=true;
			return '\n'; //So we look like classic YACC example
		}
		else
			return 0;
}
	s = st.nextToken();
	try{
		d = Double.valueOf(s);/*this may fail*/
		yylval = new ParserVal(d.doubleValue()); //SEE BELOW
		return NUMBER;
	}
	catch (Exception e){}
	if(esVariable(s)){
		if(s.equals("==")){
			return COMP;
		}
		if(s.equals("!=")){
			return DIFERENTES;
}
		if(s.equals("<")){
			return MEN;
		}
		if(s.equals("<=")){
			return MENI;
		}
		if(s.equals(">")){
			return MAY;
		}
		if(s.equals(">=")){
			return MAYI;
		}
		if(s.equals("&&")){
			return AND;
		}
		if(s.equals("||")){
			return OR;
		}
		if(s.equals("if")){
			return IF;
		}
		if(s.equals("else")){
			return ELSE;
		}
		if(s.equals("while")){
			return WHILE;
}
        if(s.equals("for")){ 
            return FOR;
        }

        /* AÑADIDO: Lógica para detectar si es una función como 'Imprimir' */
        boolean esFuncion = false;
		Object objeto = tablaDeSimbolos.encontrar(s);
		if(objeto instanceof Funcion){
			funcionAux = (Funcion)objeto;
			yylval = new ParserVal(objeto);			
			esFuncion = true;
			return FNCT;
		}
		if(!esFuncion){
			yylval = new ParserVal(s);
			return VAR;
		}
	}
	else{
        if(s.equals("^")){ 
            return '^';
        }
		tok = s.charAt(0);
	}
	//System.out.println("Token: " + tok);
	return tok;
}

// AÑADIDO: '[' y ']' a los reservados para que 'Imprimir' se detecte como FNCT
String reservados[] = {"=", "{", "}", ",", "*", "+", "-", "(", ")", "|", "[", "]", ";", "!", "^"}; 
boolean esVariable(String s){
	boolean cumple = true;
	for(int i = 0; i < reservados.length; i++)
		if(s.equals(reservados[i]))
			cumple = false;
	return cumple;
}

void dotest() throws Exception{
    // Cargamos la función 'Imprimir' en la tabla de símbolos
    tablaDeSimbolos.insertar("Imprimir", new MaquinaDePila.Imprimir());

	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
while (true){
		huboError = false;
		try{
			ins = in.readLine();
		}
		catch (Exception e){}
		st = new StringTokenizer(ins);
		newline=false;
		maquina = new MaquinaDePila(tablaDeSimbolos);
		yyparse();
		if(!huboError)
			maquina.ejecutar();
}
}

public static void main(String args[]) throws Exception{
	Parser par = new Parser(false);
	par.dotest();
}
//#line 505 "Parser.java"
//###############################################################
// method: yylexdebug : check lexer state
//###############################################################
void yylexdebug(int state,int ch)
{
String s=null;
  if (ch < 0) ch=0;
  if (ch <= YYMAXTOKEN) //check index bounds
     s = yyname[ch];    //now get it
  if (s==null)
    s = "illegal-symbol";
  debug("state "+state+", reading "+ch+" ("+s+")");
}





//The following are now global, to aid in error reporting
int yyn;       //next next thing to do
int yym;       //
int yystate;   //current parsing state from state table
String yys;    //current token string


//###############################################################
// method: yyparse : parse input and execute indicated items
//###############################################################
int yyparse()
{
boolean doaction;
  init_stacks();
  yynerrs = 0;
  yyerrflag = 0;
  yychar = -1;          //impossible char forces a read
  yystate=0;            //initial state
  state_push(yystate);  //save it
  val_push(yylval);     //save empty value
  while (true) //until parsing is done, either correctly, or w/error
    {
    doaction=true;
    if (yydebug) debug("loop"); 
    //#### NEXT ACTION (from reduction table)
    for (yyn=yydefred[yystate];yyn==0;yyn=yydefred[yystate])
      {
      if (yydebug) debug("yyn:"+yyn+"  state:"+yystate+"  yychar:"+yychar);
      if (yychar < 0)      //we want a char?
        {
        yychar = yylex();  //get next token
        if (yydebug) debug(" next yychar:"+yychar);
        //#### ERROR CHECK ####
        if (yychar < 0)    //it it didn't work/error
          {
          yychar = 0;      //change it to default string (no -1!)
          if (yydebug)
            yylexdebug(yystate,yychar);
          }
        }//yychar<0
      yyn = yysindex[yystate];  //get amount to shift by (shift index)
      if ((yyn != 0) && (yyn += yychar) >= 0 &&
          yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
        {
        if (yydebug)
          debug("state "+yystate+", shifting to state "+yytable[yyn]);
        //#### NEXT STATE ####
        yystate = yytable[yyn];//we are in a new state
        state_push(yystate);   //save it
        val_push(yylval);      //push our lval as the input for next rule
        yychar = -1;           //since we have 'eaten' a token, say we need another
        if (yyerrflag > 0)     //have we recovered an error?
           --yyerrflag;        //give ourselves credit
        doaction=false;        //but don't process yet
        break;   //quit the yyn=0 loop
        }

    yyn = yyrindex[yystate];  //reduce
    if ((yyn !=0 ) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
      {   //we reduced!
      if (yydebug) debug("reduce");
      yyn = yytable[yyn];
      doaction=true; //get ready to execute
      break;         //drop down to actions
      }
    else //ERROR RECOVERY
      {
      if (yyerrflag==0)
        {
        yyerror("syntax error");
        yynerrs++;
        }
      if (yyerrflag < 3) //low error count?
        {
        yyerrflag = 3;
        while (true)   //do until break
          {
          if (stateptr<0)   //check for under & overflow here
            {
            yyerror("stack underflow. aborting...");  //note lower case 's'
            return 1;
            }
          yyn = yysindex[state_peek(0)];
          if ((yyn != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
            if (yydebug)
              debug("state "+state_peek(0)+", error recovery shifting to state "+yytable[yyn]+" ");
            yystate = yytable[yyn];
            state_push(yystate);
            val_push(yylval);
            doaction=false;
            break;
            }
          else
            {
            if (yydebug)
              debug("error recovery discarding state "+state_peek(0)+" ");
            if (stateptr<0)   //check for under & overflow here
              {
              yyerror("Stack underflow. aborting...");  //capital 'S'
              return 1;
              }
            state_pop();
            val_pop();
            }
          }
        }
      else            //discard this token
        {
        if (yychar == 0)
          return 1; //yyabort
        if (yydebug)
          {
          yys = null;
          if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
          if (yys == null) yys = "illegal-symbol";
          debug("state "+yystate+", error recovery discards token "+yychar+" ("+yys+")");
          }
        yychar = -1;  //read another
        }
      }//end error recovery
    }//yyn=0 loop
    if (!doaction)   //any reason not to proceed?
      continue;      //skip action
    yym = yylen[yyn];          //get count of terminals on rhs
    if (yydebug)
      debug("state "+yystate+", reducing "+yym+" by rule "+yyn+" ("+yyrule[yyn]+")");
    if (yym>0)                 //if count of rhs not 'nil'
      yyval = val_peek(yym-1); //get current semantic value
    yyval = dup_yyval(yyval); //duplicate yyval if ParserVal is used as semantic value
    switch(yyn)
      {
//########## USER-SUPPLIED ACTIONS ##########
case 4:
//#line 41 "P5.y"
{yyval = val_peek(1);}
break;
case 5:
//#line 42 "P5.y"
{yyval = val_peek(2);}
break;
case 6:
//#line 45 "P5.y"
{				
				yyval = new ParserVal(maquina.agregarOperacion("varPush_Eval")); 
				maquina.agregar(val_peek(0).sval);
}
break;
case 7:
//#line 49 "P5.y"
{
				yyval = new ParserVal(maquina.agregarOperacion("constPush"));
				maquina.agregar(val_peek(0).dval);
			}
break;
case 8:
//#line 53 "P5.y"
{
                yyval = val_peek(0); 
                maquina.agregarOperacion("vectorCreate");
            }
break;
case 9:
//#line 57 "P5.y"
{
				yyval = new ParserVal(val_peek(0).ival);
				maquina.agregarOperacion("varPush");
		        maquina.agregar(val_peek(2).sval);
maquina.agregarOperacion("asignar");
		        maquina.agregarOperacion("varPush_Eval"); 
				maquina.agregar(val_peek(2).sval);
			}
break;
case 10:
//#line 66 "P5.y"
{ 
                yyval = new ParserVal(val_peek(1).ival);
                maquina.agregar((Funcion)(val_peek(3).obj));
            }
break;
case 11:
//#line 70 "P5.y"
{ 
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("productoPuntoOMultiplicar");
			}
break;
case 12:
//#line 74 "P5.y"
{ 
                yyval = new ParserVal(val_peek(2).ival);
                maquina.agregarOperacion("productoCruz");
            }
break;
case 13:
//#line 78 "P5.y"
{
				yyval = new ParserVal(val_peek(2).ival);
maquina.agregarOperacion("sumar");
			}
break;
case 14:
//#line 82 "P5.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("restar");
			}
break;
case 15:
//#line 86 "P5.y"
{
				yyval = new ParserVal(val_peek(1).ival);
			}
break;
case 16:
//#line 90 "P5.y"
{
				yyval = val_peek(13);
				maquina.agregar(val_peek(7).ival, val_peek(13).ival + 1);
maquina.agregar(val_peek(2).ival, val_peek(13).ival + 2);
				maquina.agregar(maquina.numeroDeElementos() - 1, val_peek(13).ival + 3);
			}
break;
case 17:
//#line 97 "P5.y"
{
				yyval = val_peek(9);
				maquina.agregar(val_peek(3).ival, val_peek(9).ival + 1);
				maquina.agregar(val_peek(0).ival, val_peek(9).ival + 2);
maquina.agregar(val_peek(0).ival, val_peek(9).ival + 3);
			}
break;
case 18:
//#line 103 "P5.y"
{
				yyval = val_peek(9);
maquina.agregar(val_peek(3).ival, val_peek(9).ival + 1);
				maquina.agregar(val_peek(0).ival, val_peek(9).ival + 2);
			}
break;
case 19:
//#line 108 "P5.y"
{
                yyval = val_peek(15);
                maquina.agregar(val_peek(10).ival, val_peek(15).ival + 1);  /* Condición*/
                maquina.agregar(val_peek(7).ival, val_peek(15).ival + 2); /* Instrucción final*/
                maquina.agregar(val_peek(3).ival, val_peek(15).ival + 3); /* Cuerpo*/
                maquina.agregar(val_peek(0).ival, val_peek(15).ival + 4); /* Final*/
            }
break;
case 20:
//#line 115 "P5.y"
{
				 maquina.agregarOperacion("comparar");
				 yyval = val_peek(2);
			}
break;
case 21:
//#line 120 "P5.y"
{
				 maquina.agregarOperacion("compararNot");
				 yyval = val_peek(2);
			}
break;
case 22:
//#line 124 "P5.y"
{
				 maquina.agregarOperacion("menor");
				 yyval = val_peek(2);
			}
break;
case 23:
//#line 129 "P5.y"
{
				 maquina.agregarOperacion("menorIgual");
				 yyval = val_peek(2);
			}
break;
case 24:
//#line 133 "P5.y"
{
				 maquina.agregarOperacion("mayor");
				 yyval = val_peek(2);
			}
break;
case 25:
//#line 138 "P5.y"
{
				 maquina.agregarOperacion("mayorIgual");
				 yyval = val_peek(2);
			}
break;
case 26:
//#line 142 "P5.y"
{
				maquina.agregarOperacion("and");
				 yyval = val_peek(2);
			}
break;
case 27:
//#line 147 "P5.y"
{
				maquina.agregarOperacion("or");
				 yyval = val_peek(2);
			}
break;
case 28:
//#line 151 "P5.y"
{
				maquina.agregarOperacion("negar");
				yyval = val_peek(0);
			}
break;
case 29:
//#line 156 "P5.y"
{yyval = new ParserVal(maquina.agregarOperacion("stop"));}
break;
case 30:
//#line 159 "P5.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_if_then_else"));
maquina.agregarOperacion("stop");/*then*/
	        maquina.agregarOperacion("stop");/*else*/
	        maquina.agregarOperacion("stop");/*siguiente comando*/
		}
break;
case 31:
//#line 166 "P5.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_while"));
	        maquina.agregarOperacion("stop");/*cuerpo*/
	        maquina.agregarOperacion("stop");/*final*/
		}
break;
case 32:
//#line 172 "P5.y"
{
            yyval = new ParserVal(maquina.agregarOperacion("_for"));
            maquina.agregarOperacion("stop");/*condicion*/
            maquina.agregarOperacion("stop");/*instrucción final*/
            maquina.agregarOperacion("stop");/*cuerpo*/
            maquina.agregarOperacion("stop");/*final*/
        }
break;
case 33:
//#line 180 "P5.y"
{ yyval = new ParserVal(maquina.agregarOperacion("nop"));}
break;
case 34:
//#line 181 "P5.y"
{yyval = val_peek(0);}
break;
case 35:
//#line 182 "P5.y"
{yyval = val_peek(2);}
break;
//#line 877 "Parser.java"
//########## END OF USER-SUPPLIED ACTIONS ##########
    }//switch
    //#### Now let's reduce... ####
    if (yydebug) debug("reduce");
    state_drop(yym);             //we just reduced yylen states
    yystate = state_peek(0);     //get new state
    val_drop(yym);               //corresponding value drop
    yym = yylhs[yyn];            //select next TERMINAL(on lhs)
    if (yystate == 0 && yym == 0)//done? 'rest' state and at first TERMINAL
      {
      if (yydebug) debug("After reduction, shifting from state 0 to state "+YYFINAL+"");
      yystate = YYFINAL;         //explicitly say we're done
      state_push(YYFINAL);       //and save it
      val_push(yyval);           //also save the semantic value of parsing
      if (yychar < 0)            //we want another character?
        {
        yychar = yylex();        //get next character
        if (yychar<0) yychar=0;  //clean, if necessary
        if (yydebug)
          yylexdebug(yystate,yychar);
        }
      if (yychar == 0)          //Good exit (if lex returns 0 ;-)
         break;                 //quit the loop--all DONE
      }//if yystate
    else                        //else not done yet
      {                         //get next state and push, for next yydefred[]
      yyn = yygindex[yym];      //find out where to go
      if ((yyn != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn]; //get new state
      else
        yystate = yydgoto[yym]; //else go to new defred
      if (yydebug) debug("after reduction, shifting from state "+state_peek(0)+" to state "+yystate+"");
      state_push(yystate);     //going again, so push state & val...
      val_push(yyval);         //for next action
      }
    }//main loop
  return 0;//yyaccept!!
}
//## end of method parse() ######################################



//## run() --- for Thread #######################################
/**
 * A default run method, used for operating this parser
 * object in the background.  It is intended for extending Thread
 * or implementing Runnable.  Turn off with -Jnorun .
 */
public void run()
{
  yyparse();
}
//## end of method run() ########################################



//## Constructors ###############################################
/**
 * Default constructor.  Turn off with -Jnoconstruct .

 */
public Parser()
{
  //nothing to do
}


/**
 * Create a parser, setting the debug to true or false.
 * @param debugMe true for debugging, false for no debug.
 */
public Parser(boolean debugMe)
{
  yydebug=debugMe;
}
//###############################################################



}
//################### END OF CLASS ##############################
