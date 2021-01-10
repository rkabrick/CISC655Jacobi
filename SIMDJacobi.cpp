#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

extern void SIMDJacobi(double *IN, double *OUT, unsigned N){
  unsigned i,j;
  for( i=1; i<N-1; ++i ) {
    #pragma omp simd
    for( j=1; j<N-1; ++j ) {
      double newVal = (1.0 / 9.0) * (
          IN[ i*N + (j-1) ] + IN[ i*N + j ] + IN[ i*N + (j+1)] + 
          IN[ (i-1)*N + (j-1)] + IN[(i-1)*N + j] + IN[(i-1)*N + (j+1)] +
          IN[(i+1)*N + (j-1)] + IN[(i+1)*N + j] + IN[(i+1)*N + (j+1)]);
      OUT[i*N + j] = newVal;
    }
  }
}