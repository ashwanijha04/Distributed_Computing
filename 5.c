// Write a program to find the number of processes, number of threads etc(Environment information)

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  int nthreads, tid, procs, maxt, inpar, dynamic, nested;


  // Starting parallel region
  #pragma omp parallel private(nthreads, tid)
  {
    tid = omp_get_thread_num();

    if(tid==0){
      printf("Getting environment information. \n" );


      nthreads = omp_get_num_threads();
      procs = omp_get_num_procs();
      maxt = omp_get_max_threads();
      inpar = omp_in_parallel();
      dynamic = omp_get_dynamic();
      nested = omp_get_nested();
    }

    printf("Number of processes: %d \n",procs);
    printf("Number of threads: %d\n", nthreads);
    printf("Max threads: %d\n", maxt);
    printf("In Parallel: %d \n",inpar);
    printf("Dynamic threads enabled: %d\n", dynamic);
    printf("Nested parallelism supported: %d\n", nested);


  }


  return 0;
}
