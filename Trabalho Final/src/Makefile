IDIR = ../include
CC = gcc -Wall
CFLAGS = -I$(IDIR) -lcunit -lm -ftest-coverage -fprofile-arcs

ODIR = obj
LDIR = ../lib

LIBS =

_DEPS = pilha.h calculadora.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testa_calculadora.o pilha.o calculadora.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testa_calc: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
