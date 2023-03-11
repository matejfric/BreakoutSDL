APPNAME=breakout

IDIR=../include
ODIR=obj

CC=gcc
CFLAGS= -pedantic -Wall -Wextra -g -fsanitize=address -O3 -I$(IDIR)
LIBS= -lSDL2_ttf -lSDL2 -lm

_DEPS = common.h defs.h gfx.h init.h input.h logic.h main.h res.h text.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = gfx.o init.o input.o logic.o main.o res.o text.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(APPNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

# removes .o files
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
