#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// IN[(i-1)*N + j -1]
// Making stores streaming, we will avoid cache pollution (keeping more of it for data reuse in the input data)
// Good candidate for stores because of aligned nature of outbound memory access
// Make stores streaming (non temporal)
extern void MultiThreadSIMDJacobi(float *IN, float *OUT, unsigned N){
  unsigned i,j;
  #pragma omp parallel for
  for( i=1; i<N-1; ++i ) {
    #pragma omp simd
    #pragma vector nontemporal
    for( j=1; j<N-1; ++j ) {
      float newVal = (1.0 / 9.0) * (
          IN[ i*N + (j-1) ] + IN[ i*N + j ] + IN[ i*N + (j+1)] + 
          IN[ (i-1)*N + (j-1)] + IN[(i-1)*N + j] + IN[(i-1)*N + (j+1)] +
          IN[(i+1)*N + (j-1)] + IN[(i+1)*N + j] + IN[(i+1)*N + (j+1)]);
      OUT[i*N + j] = newVal;
    }
  }
}
 
