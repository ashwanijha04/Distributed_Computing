#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NRA 62
#define NCA 15
#define NCB 7


int main(int argc, char* argv[]){
  int tid, nthreads, i,j,k, chunk=10;
  int a[NRA][NCA], b[NCA][NCB], c[NRA][NCB];

  #pragma omp parallel shared(a,b,c, nthreads, chunk) private(tid, i,j,k)
  {
    tid = omp_get_thread_num();

    if(tid == 0){
      nthreads = omp_get_num_threads();
      printf("Starting matrix multiplication with %d threads\n", nthreads);

    }


    // Initializing matrices
    #pragma omp for schedule(static, chunk)
    for(i=0; i<NRA; i++)
      for(j=0;j<NCA;j++)
        a[i][j] = i+j;


    #pragma omp for schedule(static, chunk)
    for(i=0; i<NCA; i++)
      for(j=0;j<NCB;j++)
        b[i][j] = i*j;

    #pragma omp for schedule(static, chunk)
    for(i=0; i<NRA; i++)
      for(j=0;j<NCB;j++)
        c[i][j] = 0.0;


    // multiplication
    printf("Thread %d starting multiplication\n", tid);

    #pragma omp for schedule(static, chunk)
    for(i=0;i<NRA;i++){
      printf("Thread %d did row %d\n", tid, i);
      for(j=0; j<NCB; j++)
        for(k=0; k<NCA; k++)
          c[i][j] += a[i][k]*b[k][j];
    }

  }

  // Print results
    for(i=0; i<NRA; i++){
      for(j=0; j<NCB; j++){
        printf("%d ", c[i][j]);
      }
      printf("\n" );
    }




  return 0;
}
