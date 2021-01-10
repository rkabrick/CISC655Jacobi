#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <vector>
#include <omp.h>

// The elements of a vector are stored contiguously, meaning that if v is a vector where T is some type other than bool, then it obeys the identity &v[n] == &v[0] + n for all 0 <= n < v.size().
extern void SequentialJacobi(double *IN, double *OUT, unsigned N);

// Full Opt
extern void MultiThreadSIMDJacobi(double *IN, double *OUT, unsigned N);

void flush(std::vector<double*> g, unsigned N){
  unsigned i;
  for( i=0; i<N; i++ ){
    g[i]++;
  }
}

// 1GB Array = 8 Bytes * N^2 -> N ~ 11180 ( Should be big enough to annhilate any cache )
// Must be on the heap because stack probably can't expand that much
void GenMat(unsigned N){
  std::vector<double>* NewMat = new std::vector<double>();
  NewMat->reserve(N*N);
  srand(1);

  for( unsigned i=0; i<N; i++ ){
    for( unsigned j=0; j<N; j++ ){
      NewMat->push_back(rand());
    }
  }
}


int main(int argc, char** argv){

  unsigned methodNum = atoi(argv[1]);
  long unsigned N;
  if( argc <= 2 ) {
    N = 10000;
  }
  else {
    N = atoi(argv[2]);
  }
  
  // Generate Matrix 
  std::vector<double>* NewMat = new std::vector<double>();
  NewMat->reserve(N*N);
  //delete(NewMat);
  std::cout << &NewMat[4] << std::endl;
  srand(1);

  for( unsigned i=0; i<N; i++ ){
    for( unsigned j=0; j<N; j++ ){
      NewMat->push_back(rand());
    }
  }
  switch(methodNum) {
      case 0 :
        std::cout << "serial" << std::endl;
        break;
      case 1 :
        std::cout << "omp simd" << std::endl;
        break;
      case 2 :
        std::cout << "asdf" << std::endl;
        break;
      default : 
        std::cout << "default" << std::endl;
        break;
  }
  std::cout << N << std::endl;


}