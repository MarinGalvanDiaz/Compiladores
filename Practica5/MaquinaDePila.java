import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Stack;

public class MaquinaDePila {
    
    private int contadorDePrograma;
    private ArrayList  memoria;
    private Stack pila;
    private TablaDeSimbolos tabla;
    private boolean stop = false;
    
    public MaquinaDePila(TablaDeSimbolos tabla){
        contadorDePrograma = 0;
        memoria = new ArrayList<Method>();
        pila = new Stack();
        this.tabla = tabla;
    }
    
    public int numeroDeElementos(){
        return memoria.size() + 1;
    }
    
    //Funciones que se escriben en memoria
    public int agregarOperacion(String nombre){
        int posicion = memoria.size();
        try{
            memoria.add(this.getClass().getDeclaredMethod(nombre, null));
            return posicion;
        }
        catch(Exception e ){}
        return -1;
    }
    
    public int agregar(Object objeto){
        int posicion = memoria.size();
        memoria.add(objeto);
        return posicion;
    }
    
    public void agregar(Object objeto, int posicion){
        memoria.remove(posicion);
        memoria.add(posicion, objeto);
    }
    
    //Funciones que la máquina ejecuta sobre la pila
    private void sumar(){
        Object B = pila.pop();
        Object A = pila.pop();
        if(A instanceof Vector3D && B instanceof Vector3D)
            pila.push(VectOp.suma((Vector3D)A, (Vector3D)B));
        else 
            pila.push((double)A + (double)B); // Suma escalar
    }
    
    private void restar(){
        Object B = pila.pop();
        Object A = pila.pop();
        if(A instanceof Vector3D && B instanceof Vector3D)
            pila.push(VectOp.resta((Vector3D)A, (Vector3D)B));
        else 
            pila.push((double)A - (double)B); // Resta escalar
    }

    /* Método 'multiplicar' ELIMINADO */

    // NUEVO: Maneja '*' (Producto Punto o Multiplicación Escalar)
    private void productoPuntoOMultiplicar(){
        Object B = pila.pop();
        Object A = pila.pop();
        if(A instanceof Vector3D && B instanceof Vector3D)
            pila.push(VectOp.productoPunto((Vector3D)A, (Vector3D)B)); // Retorna double
        else 
            pila.push((double)A * (double)B); // Multiplicación escalar
    }
    
    // NUEVO: Maneja '^' (Producto Cruz)
    private void productoCruz(){
        Object B = pila.pop();
        Object A = pila.pop();
        if(A instanceof Vector3D && B instanceof Vector3D)
            pila.push(VectOp.productoCruz((Vector3D)A, (Vector3D)B)); // Retorna Vector3D
        else {
            // Error: Producto cruz solo entre vectores
            System.out.println("Error: Producto Cruz solo aplicable a vectores");
            pila.push(null); // O manejar error
        }
    }
    
    // NUEVO: Crea un vector desde la pila
    private void vectorCreate(){
        double z = (double)pila.pop();
        double y = (double)pila.pop();
        double x = (double)pila.pop();
        pila.push(new Vector3D(x, y, z));
    }
    
    private void constPush(){
        pila.push(memoria.get(++contadorDePrograma));
    }
    
    private void varPush(){
        pila.push(memoria.get(++contadorDePrograma));
    }
    
    private void varPush_Eval(){
        pila.push(tabla.encontrar((String)memoria.get(++contadorDePrograma)));
    }

    private void asignar(){
        String variable = (String)pila.pop();
        Object objeto = pila.pop();
        tabla.insertar(variable, objeto);
    }
    
    // MODIFICADO: para comparar Vectores o doubles
    private void comparar(){
        Object B = pila.pop();
        Object A = pila.pop();
        if((A instanceof Vector3D) && (B instanceof Vector3D))
            pila.push(VectOp.comparar((Vector3D)A, (Vector3D)B));
        else
            pila.push((double)A==(double)B);
    }

    // MODIFICADO: para comparar Vectores o doubles
    private void compararNot(){
        Object B = pila.pop();
        Object A = pila.pop();
        if((A instanceof Vector3D) && (B instanceof Vector3D))
            pila.push(!VectOp.comparar((Vector3D)A, (Vector3D)B));
        else
            pila.push((double)A!=(double)B);
    }

    // MODIFICADO: Comparaciones solo para escalares
    private void menor(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); //Se sacan en orden inverso
        
        /* BLOQUE MATRIZ ELIMINADO */
        
        a = (double)A;
        b = (double)B;
        pila.push(a < b);
    }

    // MODIFICADO: Comparaciones solo para escalares
    private void mayor(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); 
        
        /* BLOQUE MATRIZ ELIMINADO */

        a = (double)A;
        b = (double)B;
        pila.push(a > b);
    }

    // MODIFICADO: Comparaciones solo para escalares
    private void menorIgual(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); 
        
        /* BLOQUE MATRIZ ELIMINADO */
        
        a = (double)A;
        b = (double)B;
        pila.push(a <= b);
    }

    // MODIFICADO: Comparaciones solo para escalares
    private void mayorIgual(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); 
        
        /* BLOQUE MATRIZ ELIMINADO */
        
        a = (double)A;
        b = (double)B;
        pila.push(a >= b);
    }

    private void negar(){
        pila.push(! (boolean)pila.pop());
    }

    private void and(){
        pila.push((boolean)pila.pop() && (boolean)pila.pop());
    }

    private void or(){
        pila.push((boolean)pila.pop() && (boolean)pila.pop());
    }
    
    private void stop(){
        stop = true;
    }

    private void nop(){
    }
    
    private void _while(){
        int condicion = contadorDePrograma;
        boolean continua = true;
        while(continua){
            ejecutar(condicion + 3);           
            if((boolean)pila.pop()){ //lee el resultado de la condición de la pila
                ejecutar((int)memoria.get(condicion+1));//Ejecuta el cuerpo
            }
            else{
                contadorDePrograma = (int)memoria.get(condicion+2); 
                continua = false;
            }
        }     
    }
    
    // NUEVO: Lógica para el bucle FOR
    private void _for(){
        int inicio = contadorDePrograma;
        int condicion = (int)memoria.get(inicio + 1);
        int instruccionFinal = (int)memoria.get(inicio + 2);
        int cuerpo = (int)memoria.get(inicio + 3);
        int finalDeBucle = (int)memoria.get(inicio + 4);

        // La instrucción de inicialización ya se ejecutó (está en 'instrucciones' antes del ';')
        
        boolean continua = true;
        while(continua){
            ejecutar(condicion); // Ejecuta la condición
            if((boolean)pila.pop()){
                ejecutar(cuerpo); // Ejecuta el cuerpo
                ejecutar(instruccionFinal); // Ejecuta la instrucción final (ej. i = i + 1)
            } else {
                continua = false;
            }
        }
        contadorDePrograma = finalDeBucle;
    }
    
    private void _if_then_else(){
        int condicion = contadorDePrograma;
        ejecutar(condicion + 4); //Evalúa la condicion
        boolean resultado = true;
        try{
            resultado = (boolean)pila.pop();
        }
        catch(Exception e ){
        }
        if(resultado){ //lee el resultado de la condición de la pila
            ejecutar((int)memoria.get(condicion+1));//Ejecuta el cuerpo
        }
        else{
            ejecutar((int)memoria.get(condicion+2));
        }
        contadorDePrograma = (int)memoria.get(condicion+3);
    }

    //Métodos para la ejecución
    public void ejecutar(){
        contadorDePrograma = 0;
        stop = false;
        while(contadorDePrograma < memoria.size())
            ejecutarInstruccion(contadorDePrograma);
    }
    
    public void ejecutar(int indice){//ejecuta hasta que se encuentra Stop     
        contadorDePrograma = indice;
        while(stop == false && contadorDePrograma < memoria.size()){ //Añadida comprobación de límites
            ejecutarInstruccion(contadorDePrograma);
        }
        stop = false;
    }
    
    public void ejecutarInstruccion(int indice){
        //System.out.println("Ejecutando: " + indice);
        try{         
            Object objetoLeido = memoria.get(indice);
            if(objetoLeido instanceof Method){
                Method metodo = (Method)objetoLeido;
                metodo.invoke(this, null);
            }
            if(objetoLeido instanceof Funcion){
                Funcion funcion = (Funcion)objetoLeido;
                pila.push(funcion.ejecutar(pila.pop()));
            }
            contadorDePrograma++;
        }
        catch(Exception e){
            // e.printStackTrace(); // Útil para depurar
        }
    }
    
    // 'Imprimir' se mantiene, funciona con cualquier Object.toString()
    public static class Imprimir implements Funcion{
        @Override
        public Object ejecutar(Object A) {
            System.out.println("" + A);
            return A;
        }
    }

    /* CLASES INTERNAS 'Invertir' y 'Sumar' ELIMINADAS */
}
