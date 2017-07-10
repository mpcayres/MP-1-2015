IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -lcunit

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = pilha.h parentizacao.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testa_parentizacao.o pilha.o parentizacao.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testa_parent: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
