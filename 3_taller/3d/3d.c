#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

void open(char *filename);
void count(FILE *data);

int main(int argc, char **argv){
  
  FILE *data;
  size_t x,y,i,j,a;
  int m3=0,m1=0,m2=0;
  open(argv[1]);
  count(data);
  
  // dar memoria 
  
  malloc(x*y);

  
  /*
  //hacer la matriz provisional
  gsl_matrix *P=gsl_matrix_alloc(y,x);
  gsl_matrix_fscanf(data, P);

  // sacar la media para cada dimension 
  gsl_vector *m= gsl_vector_alloc(3);
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      if(i==0)
	{
	  m1+= gsl_matrix_get(P,j,i);
	}
      if(i==1)
	{
	  m2+= gsl_matrix_get(P,j,i); 
	}
      if(i==2)
	{
	  m3+= gsl_matrix_get(P,j,i);
	}
      m1/= y;  m2/= y;  m3/=y;
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
	double ei= gsl_matrix_get(P,j,i) - gsl_vector_get(m,i);
	double ea= gsl_matrix_get(P,j,a) - gsl_vector_get(m,a);
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


  for(i=0;i<x;i++){
    double eval_i= gsl_vector_get(eval,i);
    gsl_vector_view evec_i = gsl_matrix_column (evec,i);

    printf("eigenvalue %g\n", eval_i);
    printf("eigenvector = \n");
    gsl_vector_fprintf(stdout, &evec_i.vector, "%g");
  }
*/
  return 0;
}

void open(char *filename){  FILE *data;  data =fopen(filename, "r");  close(filename);}

void count(FILE *data){
  int x=0, y=0, test;  char line;
  do{test= fscanf(data, "/n", &line); 
    if(test!=EOF){      y++;    }
  }while(test!=EOF);  
  x=3;
}

