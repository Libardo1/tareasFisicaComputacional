#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Declarar funciones

float *gen_empty(float *vector, int n);
float *gen_x(float *vector, float x0, float xf, int n);
float *gen_u_initial(float *vector, float *x, float L, int n);
void iterations(int n_time, float *u_future, float *u_present, float *u_past, float r, int n_points);
void copy(float *vectorfrom, float *vectorto, int n);
void write_row_txt(FILE *fileout, float t, float *u, int n_points);

// Main 

int main(int argc, char **argv){
  
  int n_points = 0, i = 0, n_time = 120, j = 0, nt = 0.0;
  float delta_x = 0.0, delta_t = 0.0, c = 0.0, r = 0.0, x0 = 0.0, xf = 0.0, rho = 0.0, T = 0.0, L = 0.0;
  float *x = NULL, *u_initial = NULL, *u_future = NULL, *u_past = NULL, *u_present = NULL;
  FILE *fileout; 
  char filename[20];
 
  // Condiciones inciales y parametros relevantes// 
  n_points = 101;
  T = 40.0;
  L = 100.0;
  rho = atof(argv[1]);
  c = sqrt(rho/T);
  x0 = 0.0;
  xf = 101.0;
  delta_t = 1.0;
  delta_x = 1.0;
  r = c*(delta_t/delta_x);

  // Inicializar
  u_initial = gen_empty(u_initial, n_points);
  u_future = gen_empty(u_future, n_points);
  u_past = gen_empty(u_past, n_points);
  u_present = gen_empty(u_present, n_points);
  x = gen_empty(x, n_points);
  x = gen_x(x, x0, xf, n_points);
  
  // Primera iteracion. 
  sprintf(filename, "string_%f.dat", rho);
  fileout = fopen(filename,"w");

  u_initial = gen_u_initial(u_initial, x, L, n_points);  
  ///// Escribir fila t = 0  
  write_row_txt(fileout, 0.0, u_initial, n_points);
  
  u_future[0] = 0.0;
  for (i=1; i<n_points-1; i++){
    u_future[i] = u_initial[i] + (r*r/2.0)*(u_initial[i+1] - 2*u_initial[i] + u_initial[i-1]);
  }
  copy(u_initial, u_past, n_points);
  copy(u_future, u_present, n_points);
  ///// Escribir fila t = 1
  write_row_txt(fileout, 1.0, u_present, n_points);
  
  // Siguientes iteraciones
  for(j=2; j<n_time+1; j++){
    u_future[0] = 0.0;
    for(i=1; i<n_points-1; i++){
      u_future[i] = 2*(1 - r*r)*u_present[i] - u_past[i] + (r*r)*(u_present[i+1] + u_present[i-1]);
    }
    copy(u_present, u_past, n_points);
    copy(u_future, u_present, n_points); 
    ///// Escribir filas
    write_row_txt(fileout, j, u_present, n_points);
  }
  return 0;
}

// Funciones

float *gen_empty(float *vector,int n){
 int i=0;
  if(!(vector = malloc(sizeof(float)*n))){
    fprintf(stderr, "Problem with memory allocation");
  }
  for(i=0; i<n; i++){
    vector[i] = 0.0;
  }
  return vector;
}

float *gen_x(float *vector, float x0, float xf, int n){
  float change = 0.0;
  int i = 0;
  change = (xf-x0)/n;
  vector[0] = x0;
  vector[n] = xf;
  for( i=1; i<n; i++){
    vector[i] = vector[i-1] + change;
  }
  return vector;
}
 
 float *gen_u_initial(float *vector, float *x, float L, int n){
   int i = 0;
   vector[0] = 0.0;
   vector[n-1] = 0.0;
   for(i=1; i<n-1; i++){
     if ( x[i] <= 0.8*L ){
       vector[i] = 1.25*x[i]/L;
     }
     else{
      vector[i] = 5 - 5*x[i]/L;
    }
  }
  return vector;
}

void iterations(int n_time, float *u_future, float *u_present, float *u_past, float r,int n_points){
  int i = 0,j = 0;
  for(j = 0; j<n_time; j++){
    for(i = 1; i<n_points-1; i++){
      u_future[i] = 2*(1 - r*r)*u_present[i] - u_past[i] + (r*r)*(u_present[i+1] + u_present[i-1]);
    }
    copy(u_future, u_present, n_points);
  }
}

void copy(float *vector1, float *vector2, int n){
  int i=0;
  for(i=0; i<n; i++){
    vector2[i] = vector1[i];
  }
}

void write_row_txt(FILE *fileout, float t, float *u, int n_points){
  int i=0;
  //  fprintf(fileout, "%f ", t);
  for(i=0; i<(n_points); i++){
    fprintf(fileout,"%f ", u[i]);
  }  
  fprintf(fileout, "\n");
}
