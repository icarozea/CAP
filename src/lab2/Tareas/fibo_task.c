/* To compile Classic Compiler: icc -o fibo_task.icc fibo_task.c -qopenmp -qopt-report */
/*                               more fibo_task.optrpt */
/*                               ./fibo_task.icc 2 10 */
#include <stdio.h>
#include <omp.h>

long comp_fib_numbers(int n)
{
	long fnm1, fnm2, fn;
	if ( n == 0 || n == 1 ) return(1);
	if ( n<20 ) return(comp_fib_numbers(n-1) +comp_fib_numbers(n-2));

	#pragma omp task shared(fnm1)
	{fnm1 = comp_fib_numbers(n-1);}
	#pragma omp task shared(fnm2)
	{fnm2 = comp_fib_numbers(n-2);}
	#pragma omp taskwait
	fn = fnm1 + fnm2;

	return(fn);
}


int main(int argc, char* argv[]) {
	int thread_count, n, i;
	long long fibo;

	if (argc != 3) {
		printf("usage:  ./exec <thread count> <number of Fibonacci numbers>\n");
	}
	thread_count = atoi(argv[1]); 
	omp_set_num_threads(thread_count);
	n = atoi(argv[2]);

	double start = omp_get_wtime();

#pragma omp parallel shared(n)
{
	#pragma omp single
	fibo = comp_fib_numbers(n);
}

	double stop = omp_get_wtime();

	printf("The n Fibonacci number:\n");
	printf("%d\t%lld\n", n, fibo);

	printf("Computed in %f s.\n", stop-start);

	return 0;
}  /* main */
