#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#include "/afs/csail.mit.edu/proj/courses/6.172/cilkutil/include/cilktools/cilkview.h"

// compute the dot product of two vectors.
int dot_product(int* v, int* u, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += v[i] * u[i];
  }
  return sum;
}

// compute matrix * vector
void multiply_matrix_vector(int* matrix, int* vector, int* output, int n) {
  for (int i = 0; i < n; i++) {
    output[i] = dot_product(&matrix[i*n], vector, n);
  }
}

int main(int argc, char **argv) {
  // Create create a random matrix
  srand(42);
  int n = 40000;
  int* matrix = (int*) malloc(sizeof(int) * n * n);
  int* vector = (int*) malloc(sizeof(int) * n);
  int* output = (int*) malloc(sizeof(int) * n);


  for (int i = 0; i < n*n; i++) {
    matrix[i] = rand();
  }

  for (int i = 0; i < n; i++) {
    vector[i] = rand();
  }

  cilkview_data_t start;
  cilkview_data_t end;

  __cilkview_query(start);
  multiply_matrix_vector(matrix, vector, output, n);
  __cilkview_query(end);

  printf("Runtime: %f seconds \n", (end.time - start.time) / 1000.0);

  // This sum allows you to verify that your changes don't affect the output.
  int sum = 0;
  for (int i = 0; i < n*n; i++) {
    sum += matrix[i];
  }
  printf("Sum of entries is %d \n", sum);
  return 0;
}

