CC   = icc

EXE   = main 

SOURCES    = main.c


OBJS    = stencil.o pngio.o main.o 

CFLAGS     = -O2 -Iinclude/
NVCFLAGS   = $(CFLAGS)

LIBS =  -lm -Llib/ -lpng

SOURCEDIR = .

$(EXE) :$(OBJS) 
	$(CC) $(CFLAGS)  -o $@ $? -I. $(LIBS)

$(SOURCEDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I.
clean:
	rm -f $(OBJS) $(EXE)
