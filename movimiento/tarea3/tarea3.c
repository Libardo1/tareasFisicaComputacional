#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_matrix.h>

void open(char *filename);
void count(FILE *data);

int main(int argc, char **argv){
  
  FILE *data;
  int x,y,i,j;
  
  open(argv[1]);
  count(*data);
  //hacer la matriz provisional
  gsl_matriz *P=gsl_matriz_alloc(y, x);
  gsl_matriz_fscanf( *data, *P);
  
  // diferenciar datos
  gsl_vector *M=gsl_vector_alloc(y);
  gsl_vector *Y=gsl_vector_alloc(y);

  gsl_matrix_get_col(*M, *P,1);
  gsl_matrix_get_col(*Y, *P,0);
  

  // operar los elementos de la matriz M para obtener la matriz X de datos
  
  gsl_matrix *X= gsl_matrix_alloc(y,3);
  
  for(i=0;i<3;i++){
    for(j=0;j<y;j++){
      if(i==0){
	gsl_matrix_set(*X,i,j,1);
      }
      if(i==1){
	double number= gsl_vector_get(*M,j);
	gsl_matrix_set(*X,i,j,number);
      }
      if(i==2){
	double number= gsl_vector_get(*M,j);
	double cnumber= number*number;
	gsl_matrix_set(*X,i,j,cnumber);
      }
    }
  }

  // hacer la transpuesta de la matriz X, se crea XT
  
  gsl_matrix *XT= gsl_matrix_alloc(3,y);
  gsl_matrix_transpose_mencpy(*XT,*X);
  
  
  

  return 0;
}

/* abrir el archivo y guardar el archivo */
void open(char *filename){
  FILE *data;
  data =fopen(filename, "r");
  close(filename);
}

/* contar el numero de filas y columnas del archivo*/
void count(FILE *data){
  int x=0, y=0, test;
  char line;
  float num;
  char text[250];
  do{test= fscanf(data, "/n", &line); if(test!=EOF){y++;}}while(test!=EOF); 
  //  do{test= fgets(data,"%s", &text); if(test==" "){x++;}}
  x=2;
}

/* /*hacer la matriz provisional X*/

/*  hacer el vector Y
  hacer la matriz con los datos bien 
  hacer la transpuesta
  sacar la inversa
*/