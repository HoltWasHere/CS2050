all: lab10.c queue.o trees.o
	gcc -DTEST lab10.c queue.o trees.o -o lab10
	
queue.o: queue.c
	gcc -DTEST -c queue.c
	
trees.o: trees.c
	gcc -DTEST -c trees.c
	
clean:
	rm lab10
	rm queue.o
	rm trees.o
