// MUltiply a matrix by a vector

#include <stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){

  int rows, cols, vectorSize;

  double **matrix, *vector, *result, *checkOutput;

  int i,j;

  // Read the matrix rows, cols, vectorSize
  printf("Enter the number of rows, columns and the size of the vector.");
  scanf("%d%d%d", &rows, &cols, &vectorSize);

  if(rows==0 || cols==0 || vectorSize==0){
    printf("Please enter positive values.\n");
    exit(1);
  }

  if(cols != vectorSize){
    printf("Multiplication is not possible. Please check matrix and vector dimensions.");
  }

  // Creating memory for the matrix and initializing the matrix with i+j.

  matrix = (double*)malloc(sizeof(double)*rows);
  for(i=0; i<rows; i++){
    matrix[i] = (double*)malloc(sizeof(double)*cols);
    for(j=0; j<cols; j++){
      matrix[i][j] = i+j;
    }
  }

  // Print the matrix if you want to.

  // We have the matrix. We need the vector now.

  vector = (double*)malloc(sizeof(double)*vectorSize);


  // Initialize the vector

  for(i=0; i<vectorSize; i++){
    vector[i] = i;
  }

  result = (double*)malloc(sizeof(double)*rows);
  checkOutput = (double*)malloc(sizeof(double)*rows);

  // Initialize result and checkOutput

  for(i=0; i<rows; i++){
    result[i] = 0;
    checkOutput[i] = 0;
  }


  // Parallel computation

  omp_set_num_threads(32);

  #pragma omp parallel for
  for(i=0; i<rows; i++){
    for(j=0; j<cols; j++){
      result[i] += matrix[i][j] * vector[j];
    }
  }

  // Serial Computation

  for(i=0; i<rows; i++){
    for(j=0; j<cols; j++){
      checkOutput[i] += matrix[i][j] * vector[j];
    }
  }

  // Check the serial calculation
  for(i=0; i<rows; i++){
    if(checkOutput[i] == result[i])
      continue;
    else
      printf("There is a difference in serial and parallel computaion.\n");
  }

  // Print the results

  for(i=0; i<rows; i++){
    printf("%lf\n",result[i]);
  }

  free(vector);
  free(result);
  free(matrix);
  free(checkOutput);


}
