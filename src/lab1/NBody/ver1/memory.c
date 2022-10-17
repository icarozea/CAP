
#include <malloc.h>
#include <stdlib.h>
#include "nbody.h"

body* get_memory(int nBodies)
{
	body *p = (body*)malloc(nBodies*sizeof(body));
	p -> m = (float*) malloc(sizeof(float)*nBodies);
	p -> x = (float*) malloc(sizeof(float)*nBodies);
	p -> y = (float*) malloc(sizeof(float)*nBodies);
	p -> z = (float*) malloc(sizeof(float)*nBodies);
	p -> vx = (float*) malloc(sizeof(float)*nBodies);
	p -> vy = (float*) malloc(sizeof(float)*nBodies);
	p -> vz = (float*) malloc(sizeof(float)*nBodies);
	return p;
}

void free_memory(body *p)
{
	free(p -> m);
	free(p -> x);
	free(p -> y);
	free(p -> z);
	free(p -> vx);
	free(p -> vy);
	free(p -> vz);
}

void randomizeBodies(body *data, int n) {
	for (int i = 0; i < n; i++) {
		data -> m[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

		data -> x[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data -> y[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data -> z[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

		data -> vx[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data -> vy[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data -> vz[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
	}
}

