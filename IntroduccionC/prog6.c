// Programa para practicar con strings

#include <stdio.h>

#define TAM_V 20

int main()
{
  char v[TAM_V];
  char *p;
  int i;

  p = v;

  for (i = 0; i < TAM_V - 1; i++, p++)
    *p = 'a';

  *p = '\0';

  p = v;
  p = "texto modificado";

  printf("p apunta al contenido: %s\n", p);

  printf("v contiene: %s\n", v);
}
