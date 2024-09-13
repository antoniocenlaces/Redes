#include <stdio.h>

int main()
{
  int V[10] = {5,10,15,20,25,30,35,40,45,50};
  int *p;
  int i, suma = 0;

  p = V;

  /* valor de variable p y de la  constante V */
  printf("\n");
  printf("Valor de la variable p: %x\n", p); 
  printf("Valor de V:             %x\n", V); 
  printf("Dirección del primer elemento de V:  %x \n", &V[0]); 
  printf("Dirección del segundo elemento de V: %x \n\n", &V[1]); 


  /* aritmética de punteros */
  printf("Valor de la variable p:    %x\n", p); 
  printf("Valor de la expresión p+1: %x\n\n", p+1); 


  printf("Valor de la expresión *(p+1): %d\n", *(p+1)); 
  printf("Valor de la expresión *p+1:   %d\n\n", *p+1); 

  /* suma elementos con sintaxis vector */
  for (i = 0; i < 10; i++) suma = suma + V[i];

  printf("Valor de suma: %d\n", suma);
}
