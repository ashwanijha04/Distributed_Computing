#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 65535
#define MINUS_INFINITY -9999

int main(){
  int *array;
  int i, numberOfElements, cur_max, cur_value;
  omp_lock_t MAXLOCK;

  printf("Enter the number of elements. \n");
  scanf("%d", &numberOfElements);

  if(numberOfElements<=0){
    printf("Can't store the array.\n");
    exit(1);
  }

  array = (int*)malloc(sizeof(int) * numberOfElements);

  // Allocate random numbers to array
  srand(MAX);

  // Initialize
  for(i=0; i<numberOfElements; i++){
    array[i] = rand();
  }


  // Starting the lock

  omp_set_num_threads(8);
  omp_init_lock(&MAXLOCK);
  cur_max = MINUS_INFINITY;

  #pragma omp parallel for
  for(i=0; i<numberOfElements; i++){
    if(array[i] > cur_max){
      omp_set_lock(&MAXLOCK);
      if(array[i] > cur_max)
        cur_max = array[i];
      omp_unset_lock(&MAXLOCK);
    }
  }

  // Destroy the lock
  omp_destroy_lock(&MAXLOCK);

  // Serial calculation
  // Serial calculation
	cur_value = array[0];
	for(int i=0; i<numberOfElements; i++){
		if(array[i]>cur_value){
			cur_value = array[i];

		}
	}

	// Check output validity
	if(cur_value == cur_max){
		printf("The max value is same in both serial and parallel cases.\n");
	}
	else{
		printf("The max value is not same in serial and parallel cases.\n");
		exit(1);
	}

	free(array);
  printf("Largest number in the given array is %d\n", cur_max);



}
