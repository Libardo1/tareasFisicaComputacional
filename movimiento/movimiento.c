#include <stdlib.h>
#include <stdio.h>
 
void abrir (char *filename);
void count (FILE *archivo);
float *load(FILE *data,int *nx, int *ny);
float *transpose(float *matriz, int *nx, int *ny);
void print(float *m, int *nx, int *ny);

int main (int argc, char **argv){

  float *matriz;
  FILE *data;
  int nx=0;
  int ny=0;
  float *transpuesta;
  int test;
  char line;

  abrir(argv[0]);

  count(data);

  *matriz=load(data,nx,ny);

  *transpuesta=transpose(matriz, nx, ny);

  print(matriz,nx,ny);

  return 0;
}


/* abrir y guardar el archivo*/
void abrir(char *filename){
  FILE *data;
  data = fopen(filename, "r");
  close(filename);}


/* funcion que cuenta las filas y columnas*/
void count(FILE *archivo){
  int test, nx, ny;
  char line;
  do{
    test = fscanf(archivo,"\n", &line);
    if(test!=EOF){
      nx++;
    }
  }while(test!=EOF);
}


/* funcion que carga el array*/
float *load(FILE *data,int *nx, int *ny){
  int i,j;
  float *array;
  for (j=0; j<(*ny);j++)
    {
      for (i=0; i<(*nx); i++)
    {
      fscanf(data, "%f %f",array[i+j] ,array[i+j]);
    }
    }
  return array;
}

/* funcion que hace la transpuesta*/
float *transpose(float *matriz, int *nx, int *ny){
  int i,j,pos_ij, pos_ji;
  float tmp;
  float *m;

  for(i=0;i<*nx;i++){
    for(j=i;j<*ny;j++){
      pos_ij = i + (*nx * j);
      pos_ji = j + (*nx * i);
     
      tmp = m[pos_ij];
      m[pos_ij] = m[pos_ji];
      m[pos_ji] = tmp;
    }
  }
  return m;
}

/* funcion que imprime una matriz*/
void print(float *m, int *nx, int *ny){
  int i,j,pos;
  fprintf(stdout, "\n");
  for(i=0;i<*nx;i++){
    for(j=0;j<*ny;j++){
      pos = i + (*nx * j);
      fprintf(stdout, " %f ",m[pos]);
    }
    fprintf(stdout, "\n");
  }
  fprintf(stdout, "\n");
}
