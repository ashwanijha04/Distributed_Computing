#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX 65536



int main(){
  int *array;
  int i;
  int cur_max, cur_value;
  int numberOfElements;


  // Initialize array

  printf("Enter the number of elements:\n");
  scanf("%d", &numberOfElements);

  if(numberOfElements<=0){
    printf("The array elements cannot be stored\n");
  }

  //Dynamic Memory Allocation
  array = (int*)malloc(sizeof(int)*numberOfElements);

  // Allocate Random values to the array every time rand() is run using srand()
  srand(MAX);

  for(int i=0; i<numberOfElements; i++){
    array[i] = rand();
  }

  cur_max = 0;
  omp_set_num_threads(8);


	// Parallel calculation

  #pragma omp parallel for

  for(i=0; i<numberOfElements; i++){
    if(array[i]>cur_max){
			// The critical section will be used if required, thus the two if statements.
			#pragma omp critical
			if(array[i]>cur_max)
				cur_max = array[i];

    }
  }


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
