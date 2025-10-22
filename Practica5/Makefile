# --- Variables ---

# Compilador de Java
JCC = javac

# Herramienta YACC para Java
YACC = byaccj

# Clase principal que contiene el main()
MAIN_CLASS = Parser

# Lista de tus archivos .java (EXCLUYENDO los que genera byaccj)
JAVA_SOURCES = \
    MaquinaDePila.java \
    Vector3D.java \
    VectOp.java \
    TablaDeSimbolos.java \
    Funcion.java \
    Par.java

# Archivos .java que serán generados por byaccj
GENERATED_SOURCES = Parser.java ParserVal.java

# Lista completa de todos los archivos .java
ALL_JAVA_FILES = $(JAVA_SOURCES) $(GENERATED_SOURCES)

# Lista completa de los archivos .class que se crearán
CLASSES = $(ALL_JAVA_FILES:.java=.class)

# --- Reglas ---

# Regla por defecto (la que se ejecuta si solo escribes "make")
# Compila todo el proyecto.
all: $(CLASSES)
	@echo "Proyecto compilado exitosamente."

# Regla para ejecutar el programa
# Depende de "all", así que compilará si es necesario antes de ejecutar.
run: all
	@echo "Ejecutando el parser..."
	java $(MAIN_CLASS)

# Regla para compilar los archivos .class
# Depende de que existan TODOS los archivos .java
$(CLASSES): $(ALL_JAVA_FILES)
	$(JCC) $(ALL_JAVA_FILES)

# Regla para generar los archivos del parser
# Depende del archivo .y. Se ejecutará si Parser.java o ParserVal.java
# no existen, o si P5.y es más reciente que ellos.
$(GENERATED_SOURCES): P5.y
	@echo "Detectado cambio en P5.y, generando parser..."
	$(YACC) P5.y
	@echo "Generados: $(GENERATED_SOURCES)"

# Regla para limpiar el directorio
# Elimina todos los archivos .class y los .java generados
clean:
	@echo "Limpiando archivos compilados..."
	rm -f *.class
	rm -f $(GENERATED_SOURCES)

# Evita que make confunda "all", "run" y "clean" con nombres de archivos
.PHONY: all run clean
