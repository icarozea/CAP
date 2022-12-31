CC=icx

CFLAGS=-O3 -lrt -std=c99

CFLAGS_OFFLOAD = $(CFLAGS) -fiopenmp -fopenmp-targets=spir64

NAME=heat

default: gpu

gpu: omp_offload

omp_offload:
	$(CC) $(CFLAGS_OFFLOAD) $(NAME).c -o $(NAME).omp.exe $(LIB)

clean: 
	rm -f __hmpp_*  *.exe

