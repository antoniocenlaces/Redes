#include <stdio.h>
/* Esto es una DECLARACION de una funcion,
   que imprime un mensaje, y que devuelve "void"
   (en C todas las funciones devuelven algo)
 */
void funcion()
{
  printf( "\nHello, World, Again\n");
} 

void main()
{
  printf( "\n\tHello, World!\n" ); /* funcion de la biblioteca stdio */

  funcion();  /* Esto es una LLAMADA a la funcion funcion() */
}