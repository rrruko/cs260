default: program

program: main_deq.o deq.o
	gcc -o program main_deq.o deq.o

main_deq: main_deq.c deq.h
	gcc -c main_deq.c

deq.o: deq.c deq.h
	gcc -c deq.c

clean:
	rm program deq.o