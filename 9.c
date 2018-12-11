// A-Z

#include<stdio.h>
#include<omp.h>

int main(){
  int i;
  omp_set_num_threads(4);

  #pragma omp parallel private(i)
  {
    int lettersPerThread = 26/omp_get_num_threads();
    int thread_num = omp_get_thread_num();
    int startLetter = 'a' + thread_num*lettersPerThread;
    int endLetter = startLetter + lettersPerThread;

    for(i=startLetter; i<=endLetter; i++){
      printf("%c\n",i);
    }

  }
}
