#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

FILE* opendata(char *filename);
void countdata(FILE *data, int*nx, int *ny);
double *loaddata(FILE* data, int x, int y);

int main(int argc, char **argv){
  
  FILE *data;
  double *matriz;
  int x,y,i,j,a;
  int m3=0,m1=0,m2=0;
  data=opendata(argv[1]);
  countdata(data,&x,&y);
  
  //hacer la matriz provisional
  matriz = loaddata(data,x,y);
  gsl_matrix_view P =gsl_matrix_view_array(matriz,y,x);
  // sacar la media para cada dimension
  gsl_vector *m= gsl_vector_alloc(3);
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      if(i==0)
	{
	  m1+= gsl_matrix_get(&P.matrix,j,i);
	}
      if(i==1)
	{
	  m2+= gsl_matrix_get(&P.matrix,j,i);
	}
      if(i==2)
	{
	  m3+= gsl_matrix_get(&P.matrix,j,i);
	}
      m1/= y; m2/= y; m3/=y;
    }
  }
  gsl_vector_set(m,0,m1);
  gsl_vector_set(m,1,m2);
  gsl_vector_set(m,2,m3);
  
  // crear la matriz de covarianza COV
  gsl_matrix *COV= gsl_matrix_alloc(x,x);
  for(i=0;i<x;i++){
    for(a=0;a<x;a++){
      double element=0;
      for(j=0;j<y;j++){
	double ei= gsl_matrix_get(&P.matrix,j,i) - gsl_vector_get(m,i);
	double ea= gsl_matrix_get(&P.matrix,j,a) - gsl_vector_get(m,a);
	double ee=ei*ea;
	element+=ee;
      }
      element/= (y-1);
      gsl_matrix_set(COV,i,a,element);
    }
  }
  
  // calcular los valores propios de la matriz COV
  gsl_vector *eval=gsl_vector_alloc(x);
  gsl_matrix *evec=gsl_matrix_alloc(x,x);
  gsl_eigen_symmv_workspace *w= gsl_eigen_symmv_alloc(x);

  gsl_eigen_symmv(COV,eval,evec,w);
  gsl_eigen_symmv_free(w);
  
  gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_DESC);

  //output
  FILE *fileout;
  fileout=fopen("autovectores_3D_data.dat", "w");

  for(i=0;i<x-1;i++){
    double eval_i= gsl_vector_get(eval,i);
    gsl_vector_view evec_i = gsl_matrix_column (evec,i);
    
    printf("eigenvalue %g\n", eval_i);
    printf("eigenvector = \n");
    gsl_vector_fprintf(stdout, &evec_i.vector, "%g");
    
    float evec_i_0= (float) gsl_vector_get(&evec_i.vector,0); 
    float evec_i_1= (float) gsl_vector_get(&evec_i.vector,1);
    float evec_i_2= (float) gsl_vector_get(&evec_i.vector,2);
    fprintf(fileout,"%f %f %f\n", evec_i_0, evec_i_1, evec_i_2); 
    
  } 
  close(fileout);
  return 0;
}

FILE* opendata(char *filename)
{
  FILE *data; 
  data =fopen(filename, "r"); 
  close(filename);
  return data;
}

void countdata(FILE *data,int*nx, int *ny){
  int y=0, test; char line;
  do{
    test= fgetc(data);
    if(test=='\n'){ y++; }
  }while(test!=EOF);
 *nx=3;
 *ny=y;
}

/*cargar el array*/
double *loaddata(FILE* data, int x, int y){
  int j;
  double *array;
  float a,b,c;
  
  if(!(array = malloc(sizeof(double)*x *y))){
    fprintf(stderr, "Problem with memory allocation");
    exit(1);
  }
  for(j=0;j<y; j++)
    {
      fscanf(data, "%f %f %f\n",&a,&b, &c);
	array[x*j + 0]=(double) a; 
	array[x*j + 1]=(double) b;
	array[x*j + 2]=(double) c;
    }
  return array;
}
