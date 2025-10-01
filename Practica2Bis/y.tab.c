#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
#line 1 "forma.y"

import java.util.*;
import java.lang.Math;
import java.io.*;
import java.util.StringTokenizer;
import java.awt.*;
import java.awt.event.*;
import javax.imageio.*;
import java.awt.image.*;
import javax.swing.*;
import java.lang.reflect.*;
#line 18 "y.tab.c"
#define NUMBER 257
#define LINE 258
#define DIAG 259
#define CIRCULO 260
#define RECTANGULO 261
#define COLOR 262
#define PRINT 263
#define IMAGEN 264
#define FILTRO 265
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,
    1,
};
short yylen[] = {                                         2,
    0,    2,    3,    1,    1,    2,    5,    2,    2,    3,
   10,
};
short yydefred[] = {                                      1,
    0,    4,    0,    0,    0,    5,    0,    0,    0,    2,
    0,    6,    0,    8,    9,    0,    0,    3,    0,   10,
    0,    0,    0,    7,    0,    0,    0,    0,    0,   11,
};
short yydgoto[] = {                                       1,
   11,
};
short yysindex[] = {                                      0,
  -59,    0, -256, -255, -254,    0, -253, -252, -251,    0,
  -52,    0, -249,    0,    0, -248, -247,    0, -246,    0,
 -245, -244, -243,    0, -242, -241, -240, -239, -238,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,
};
#define YYTABLESIZE 206
short yytable[] = {                                      10,
   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
   22,   23,   24,   25,   26,   27,   28,   29,   30,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    2,    3,    4,
    5,    6,    7,    0,    8,    9,
};
short yycheck[] = {                                      59,
  257,  257,  257,  257,  257,  257,   59,  257,  257,  257,
  257,  257,  257,  257,  257,  257,  257,  257,  257,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,  261,  262,   -1,  264,  265,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 265
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NUMBER","LINE","DIAG",
"CIRCULO","RECTANGULO","COLOR","PRINT","IMAGEN","FILTRO",
};
char *yyrule[] = {
"$accept : list",
"list :",
"list : list ';'",
"list : list inst ';'",
"inst : NUMBER",
"inst : RECTANGULO",
"inst : LINE NUMBER",
"inst : DIAG NUMBER NUMBER NUMBER NUMBER",
"inst : CIRCULO NUMBER",
"inst : COLOR NUMBER",
"inst : IMAGEN NUMBER NUMBER",
"inst : FILTRO NUMBER NUMBER NUMBER NUMBER NUMBER NUMBER NUMBER NUMBER NUMBER",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 80 "forma.y"

public BufferedImage leeImagen(String nombre){
   BufferedImage imagen;
   try {
      imagen = ImageIO.read(new File(nombre));     
   } catch (IOException e){
        System.err.println("no cargo "+nombre);
        return null;
   }
   return imagen;
   }
class Algo {
	Simbolo simb;
	int inst;
        Dibujable dibu;
	public Algo(int i){ inst=i; }
        public Algo(Dibujable d){ dibu=d; }
	public Algo(Simbolo s, int i){
		simb=s; inst=i;
	}
}
public void setTokenizer(StringTokenizer st){
 	this.st= st;
}
public void setNewline(boolean newline){
 	this.newline= newline;
}
//Tabla tabla;
HashMap<String, Simbolo> tabla=new HashMap<String, Simbolo>();
Maquina maq;

StringTokenizer st;
boolean newline;
int yylex(){
String s;
int tok;
Double d;
Simbolo simbo;
   if (!st.hasMoreTokens())
      if (!newline) {
         newline=true; 
	 return ';';  
      }
   else
      return 0;
   s = st.nextToken();
   try {
      d = Double.valueOf(s);
      simbo=new Simbolo(NUMBER, d.doubleValue());
      yylval = new ParserVal(new Algo(simbo, 0) );
      tok = NUMBER;
   } catch (Exception e){
   if(Character.isLetter(s.charAt(0))){
	if((simbo=tabla.get(s))!=null){
           yylval = new ParserVal(new Algo(simbo, 0));  
        }	
         tok= simbo.tipo;
    } else {
    	tok = s.charAt(0);
    }
   /*if(Character.isLetter(s.charAt(0))){
      System.out.println("s es = ("+s+")");
      if((simbo=tabla.lookup(s))==null)
         yylval = new ParserVal(new Algo(simbo, 0));
	 tok= simbo.tipo;	
      }*/ 
   }
   return tok;
}
void yyerror(String s){
   System.out.println("parser error: "+s);
}
static Parser par = new Parser(0);
static JFrame jf;
static JLabel lmuestra=new JLabel("                                 ");
static Canvas canv;
static Graphics g;
Parser(int foo){
   maq=new Maquina();
   //tabla=new Tabla();
 try {
   Method[] ma = ((Maquina)maq).getClass().getMethods();
   for (Method m : ma) {  
            Class[] parameters = m.getParameterTypes();
            if( m.getReturnType().equals(Void.TYPE) && 
                m.getParameterTypes().length==0){
                System.out.println( m.getName()  + " returns void ");
            }  
   } 
  } catch (Exception e) {
       e.printStackTrace();
  }
   tabla.put("line", new Simbolo(LINE, 0.0));
   tabla.put("diag", new Simbolo(LINE, 0.0));
   tabla.put("circulo", new Simbolo(CIRCULO, 0.0));
   tabla.put("rectangulo", new Simbolo(RECTANGULO, 0.0));
   tabla.put("color", new Simbolo(COLOR, 0.0));
   tabla.put("print", new Simbolo( PRINT, 0.0));
   tabla.put("ima", new Simbolo(IMAGEN, 0.0));
   tabla.put("fil", new Simbolo(FILTRO, 0.0));
   maq.setTabla(tabla);
   jf=new JFrame("Calcula");
   canv=new Canvas();
   canv.setSize(600,600);
   jf.add("North", new PanelEjecuta(maq, this));
   jf.add("Center", canv);
   jf.setSize( 600, 700);
   jf.setVisible(true);
   g=canv.getGraphics();
   maq.setGraphics(g);
   jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);  
}
public static void main(String args[]){ new Parser(); }
#line 278 "y.tab.c"
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: state %d, shifting to state %d (%s)\n",
                    yystate, yytable[yyn],yyrule[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
#line 18 "forma.y"
{ 
             maq.code("print"); maq.code("STOP"); return 1 ;
     }
break;
case 4:
#line 22 "forma.y"
{ ((Algo)yyval.obj).inst=maq.code("constpush");
                maq.code(((Algo)yyvsp[0].obj).simb); }
break;
case 5:
#line 24 "forma.y"
{ maq.code("rectangulo"); }
break;
case 6:
#line 25 "forma.y"
{ maq.code("constpush");
                maq.code(((Algo)yyvsp[0].obj).simb); maq.code("line");}
break;
case 7:
#line 27 "forma.y"
{ 
                     maq.code("constpush");
                     maq.code(((Algo)yyvsp[-3].obj).simb); 
                     maq.code("constpush");
                     maq.code(((Algo)yyvsp[-2].obj).simb); 
                     maq.code("constpush");
                     maq.code(((Algo)yyvsp[-1].obj).simb); 
                     maq.code("constpush");
                     maq.code(((Algo)yyvsp[0].obj).simb); 
                     maq.code("diag");}
break;
case 8:
#line 37 "forma.y"
{ maq.code("constpush");
                maq.code(((Algo)yyvsp[0].obj).simb); maq.code("circulo");}
break;
case 9:
#line 39 "forma.y"
{ maq.code("constpush");
                maq.code(((Algo)yyvsp[0].obj).simb); maq.code("color");}
break;
case 10:
#line 41 "forma.y"
{
              Simbolo s=new Simbolo();
              s.ponDibu(new Imagen(leeImagen("dalmata.jpg"), 
                (int)((Algo)yyvsp[-1].obj).simb.val, 
                (int)((Algo)yyvsp[0].obj).simb.val, jf));
              maq.code("varpush");
              maq.code(s);  
              maq.code("draw");      
      }
break;
case 11:
#line 51 "forma.y"
{  
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-8].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-7].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-6].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-5].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-4].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-3].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-2].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[-1].obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)yyvsp[0].obj).simb);
                     
                      Simbolo s=new Simbolo();
                      s.ponDibu(new Imagen(leeImagen("dalmata.jpg"), 
                100, 
                100, jf));
                      maq.code("varpush");
                      maq.code(s);  
                      maq.code("filtro");
}
break;
#line 504 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
