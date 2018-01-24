default : program

program : testDynArray.o dynamicArray.o
	gcc -o program testDynArray.o dynamicArray.o 

testDynArray : testDynArray.c dynamicArray.h
	gcc -c testDynArray.c
	
dynamicArray.o: dynamicArray.c dynamicArray.h
	gcc -c dynamicArray.c

clean :
	rm program dynamicArray.o