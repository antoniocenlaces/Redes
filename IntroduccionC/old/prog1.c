#include <stdio.h>  /* standard input/output library */

                      /* Esto es una DECLARACION de una funcion,
		         que imprime un mensaje, y que devuelve "void"
			 (en C todas las funciones devuelven algo)
		       */
void funcion(){
  printf( "\nHello, World, Again");
} 


void main()
{

  void funcion(); /* main() indica que utilizara una funcion
			  denominada asi, y declarada en este fichero
			  Esto es una ALUSION
			*/

  printf( "\n\tHello, World!\n" ); /* funcion de la stdio library */

  funcion();  /* Esto es una LLAMADA a la funcion funcion() */
}



