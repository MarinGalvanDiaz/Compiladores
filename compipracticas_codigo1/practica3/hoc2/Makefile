Gram=y.tab.c y.tab.h

all: $(Gram) 
	@gcc -o calc y.tab.c  
	@echo Compiled

$(Gram): hoc2.y
	@yacc -d hoc2.y

clean:
	@rm -f *.out  *.tab.* calc
	@echo Clean
