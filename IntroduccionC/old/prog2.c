#include <stdio.h>

void funcion();

int x=99;
int *p1;

int main()
{
  int *p2;

  p1 = &x;
  p2 = p1;

  /* valor de variable x y de las posiciones apuntadas por p1 y p2 */
  printf("\n");
  printf("Valor de la variable x: %d\n", x); 
  printf("Valor de la posición apuntada por p1: %d \n", *p1); 
  printf("Valor de la posición apuntada por p2: %d \n\n", *p2); 

  /* dirección de la variable x y valor de p1 y p2 */
  printf("Dirección de la variable x: %x \n", &x); 
  printf("Valor de la variable p1: %x \n", p1);
  printf("Valor de la variable p2: %x \n\n", p2);

  /* dirección en memoria de variables de diferente tipo */
  printf("Dirección de la variable x (global): %x \n", &x); 
  printf("Direccion de la variable p1 (global): %x \n", &p1);
  printf("Direccion de la variable p2 (local main): %x \n", &p2);
  funcion();
  printf("\n");

  return 0;
}


void funcion(){
	char c;
	c='o';
  	printf("Direccion de la variable c (local funcion): %x \n", &c);
}


