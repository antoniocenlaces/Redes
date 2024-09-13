#include <stdio.h>  

// definicion de struct
struct mi_estructura {
  char c;
  int i;
  int v[10000];
};

// declaracion de funcion
void pasoReferencia(struct mi_estructura *estructura_pila);

int main()
{
  struct mi_estructura mia;

  mia.c = '1';
  mia.i = 10;
  mia.v[1] = 100;

  printf("\nDireccion estructura: %p\n", &mia);
  printf("Direccion campo vector en estructura: %p\n\n", mia.v);

  pasoReferencia(&mia);
}

void pasoReferencia(struct mi_estructura *estructura_pila)
{
  printf("Estructura campo 1: %c\n", estructura_pila->c);
  printf("Estructura campo 2: %d\n", estructura_pila->i);
  printf("Estructura campo 3: %d\n\n", estructura_pila->v[1]);

  printf("Direccion estructura en funcion: %p\n", estructura_pila);
  printf("Direccion campo vector en estructura en funcion: %p\n\n", estructura_pila->v);
}
