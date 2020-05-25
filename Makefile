# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DEBUG 
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# pliki naglowkowe
INC =

# biblioteki
LIB =  -lm 

F =  -fopenmp

test: test.o 
	$(LOADER) $(F) $(OPT) test.o -o test $(LIB)

test.o: test.c 
	$(CCOMP) $(F) -c $(OPT) test.c $(INC)

clean:
	rm -f *.o
