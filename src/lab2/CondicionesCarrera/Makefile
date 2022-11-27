
CC=icx

CFLAGS=-O2 -g -qopt-report=2 -xhost

LIB=-lm -qopenmp

NAME=trapezoidal

default: serial

serial:
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME).serial.icc $(LIB)

clean:
	rm -rf *icc *.o *.out *.optrpt *.yaml
