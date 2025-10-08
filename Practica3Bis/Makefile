CC = gcc
CFLAGS = -g
OBJS = hoc3.tab.o init.o symbol.o math.o vector.o

hoc3: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o hoc3 -lm

hoc3.tab.o: hoc3.y
	bison -d hoc3.y
	$(CC) $(CFLAGS) -c hoc3.tab.c -o hoc3.tab.o

init.o: init.c hoc.h
	$(CC) $(CFLAGS) -c init.c

symbol.o: symbol.c hoc.h
	$(CC) $(CFLAGS) -c symbol.c

math.o: math.c hoc.h
	$(CC) $(CFLAGS) -c math.c

vector.o: vector.c hoc.h
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o hoc3.tab.[ch] hoc3