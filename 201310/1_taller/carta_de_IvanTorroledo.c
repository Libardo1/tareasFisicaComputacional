#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char **datos){

  FILE *in;  
  char mensaje[256]; 
  char ciudad[25], pais[25], nombreconocido[30], apellidoconocido[30], nombre[30];
  char sdia1[2], smes1[15], sao1[4];
  char sdia2[2], *smes2, sao2[4];
  int dia1, mes1, ao1, dia2, mes2, ao2, i;

  /*Arreglo de meses*/
  char months[12][256];
  int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};

  strcpy(months[0], "Enero");
  strcpy(months[1], "Febrero");
  strcpy(months[2], "Marzo");
  strcpy(months[3], "Abril");
  strcpy(months[4], "Mayo");
  strcpy(months[5], "Junio");
  strcpy(months[6], "Julio");
  strcpy(months[7], "Agosto");
  strcpy(months[8], "Septiembre");
  strcpy(months[9], "Octubre");
  strcpy(months[10], "Noviembre");
  strcpy(months[11], "Diciembre");

  /*Se toman los datos de entrada*/

  dia2 = atoi(datos[2]);
  ao2= atoi(datos[4]); 
  smes2= datos[3]; 
   
  /* Abrir el archivo*/
   in = fopen(datos[1], "r");

  /* Extraer los Datos */
  fscanf(in,"%s %s\n", nombreconocido, apellidoconocido);
  fscanf(in,"%s %s %s\n", sdia1 ,smes1, sao1);
  fscanf(in,"%s, ", ciudad);
  fscanf(in,"%s\n", pais); 
  fgets(mensaje, 256, in);
  fclose(in);

  /* Convertir año y dia a numero*/
  dia1= atoi(sdia1);
  ao1 = atoi(sao1);

  /*Convertir mes a numero*/
  
  for(i=0; i<=12;i++){
    if(strcmp(months[i],smes1)==0){
      mes1=i;
    }
    if(strcmp(months[i],smes2)==0){
      mes2=i;
    }
  }
  
  /*Calcular la diferencia*/  
  
  int primero= (365*ao1)+(30*mes1)+dia1;
  int ultimo = (365*ao2)+(30*mes2)+dia2;
  int diferencia=ultimo-primero;
  
  /*validar datos*/
  if(days[mes1]<dia1){
   printf("Fecha invalida1\n");
     exit(1);
   }
   if(days[mes2]<dia2){
   printf("Fecha invalida2\n");
	exit(1);
  }

  if(diferencia<=0){
    printf("Fecha Invalida3\3");  
    exit(1);
  }

 /* Escribir el mensaje*/
  printf("\nBogota, %d %s %d\n", dia2, smes2, ao2);
  printf("Hola %s %s\n", nombreconocido, apellidoconocido);
  printf("Hace unos %d dias que no te escribo, por eso quisiera aprovechar ", diferencia);
  printf("para decirte algo que siempre pense en decir: \n");
  printf("\n%s\n", mensaje);
  printf("\nEspero que nos podamos ver pronto en %s siempre he querido visitar %s.\n", ciudad, pais);
  printf("Saludos \nIvan Torroledo\n\n");
  return 0;
}

