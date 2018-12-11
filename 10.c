// How thread private clause works

#include<omp.h>
#include<stdlib.h>
#include<malloc.h>


long long factorial(long n){
  long long i, out;
  out = 1;
  for(i=1; i<n+1; i++){
    out *= i;
  }
  return out;
}

int main(int argc, char **argv){
  int i, j, threads;
  long long *x;
  long long n=12;

  if(argc>1){
    threads = atoi(argv[1]);
    if(omp_get_dynamic()){
      omp_set_dynamic(0);
    }
    printf("Called omp_set_dynamic(0)\n");
    omp_set_num_threads(threads);

  }
  printf("Max threads: %d", omp_get_max_threads());
  x = (long long *)malloc(n*sizeof(long));
  for(i=0; i<n; i++){
    x[i] = factorial(i);
  }
  j=0;

  #pragma omp parallel for firstprivate(x,j)
  for(i=1; i<n; i++){
    j+=i;
    x[i] = j*x[i-1];
  }
  for(i=0; i<n; i++){
    printf("\nFactorial(%d) = %lld x[%d] = %lld", i, factorial(i), i, x[i]);
    //return 0;
  }

}
