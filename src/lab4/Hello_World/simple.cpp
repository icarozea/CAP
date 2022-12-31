//==============================================================
// Copyright © 2020 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================
#include <omp.h>

#include <iostream>

//Compile: icpx -fiopenmp -fopenmp-targets=spir64 -qopt-report=1 simple.cpp -o simple
//run: LIBOMPTARGET_PLUGIN_PROFILE=T ./simple
//more simple.optrpt
//more simple-openmp-spir64.opt.yaml

constexpr int N = 16;
int main() {
  int is_cpu = true;
  int *data = static_cast<int *>(malloc(N * sizeof(int)));

  // Initialization
  for (int i = 0; i < N; i++) data[i] = i;
  printf("VAR is_cpu2=%i \n", is_cpu);
  // Add the target directive here, including the map clause.
#pragma omp target map(from : is_cpu) map(tofrom : data [0:N])
  {
    is_cpu = omp_is_initial_device();
    
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
      data[i] *= 2;
    }
  }
	printf("VAR is_cpu=%i \n", is_cpu);

  // Print Output
  std::cout << "Running on " << (is_cpu ? "CPU" : "GPU") << "\n";
  for (int i = 0; i < N; i++) std::cout << data[i] << "\n";

  free(data);
  return 0;
}
