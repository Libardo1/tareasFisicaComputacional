#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void copy(float *vector1, float *vector2, int n);
float *generatevector(float *vector, int m);

int main(){

  return 0;
}



void copy(float *vector1, float *vector2, int n){
  int i=0;
  for(i=0; i<n; i++){
    vector2[i] = vector1[i];
  }
}
float *generatevector(float *vect,int m){
  int i=0;
  if(!(vect = malloc(sizeof(float)*m))){
    fprintf(stderr, "Problem with memory allocation");
  }
  for( i=0 ; i<m ; i++ ){ 
    vect[i] = 0.0;
  }
  return vect;
}

