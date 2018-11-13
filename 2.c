// Example on Critical section directive

#include <stdio.h>
#include <omp.h>
#include <unistd.h>

void A(int* a){
  printf("a++\n");
  (*a)++;
}

void B(int* a){
  printf("a--\n");
  (*a)--;
}

void f(int* a){

  #pragma omp critical
  printf("I am a thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
  A(a);

  sleep(5);

  #pragma omp critical
  printf("I am a thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());

  B(a);
}


int main(int argc, char* argv){
  int i;
  int a=0;


  #pragma omp parallel for

  for(i=0; i<4; i++){
    printf("Number of threads triggered is %d\n", omp_get_num_threads());
    f(&a);
  }

  return 0;

}
