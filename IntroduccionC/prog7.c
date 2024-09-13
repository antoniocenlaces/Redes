// Programa para practicar con strings

#include <stdio.h>
#include <string.h>

#define TAM_V 20

main()
{
  char v[TAM_V];
  int i;

  for (i = 0; i < TAM_V - 1; i++)
    v[i] = 'a';

  v[TAM_V - 1]='\0';

  printf("despues de la inicializacion:\n");
  for (i = 0; i < TAM_V; i++)
    printf("v[%d] contiene el caracter ASCII numero %d: %c\n", i, v[i], v[i]);

  printf("v contiene: %s\n", v);

  // v = "texto modificado"; // funcionaria?

  strcpy(v, "texto modificado");

  printf("\ndespues del strcpy:\n");
  for (i = 0; i < TAM_V; i++)
    printf("v[%d] contiene el caracter ASCII numero %d: %c\n",i, v[i], v[i]);

  printf("v contiene: %s\n", v);

  v[10] = 0;

  printf("\ndespues de la asignacion v[10]=0:\n");
  printf("v contiene: %s\n", v);
}
