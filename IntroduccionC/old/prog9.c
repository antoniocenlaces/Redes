#include <stdio.h>  

//definicion variables globales
struct mi_estructura{
	char c;
	int i;
	int v[10000];
};

//definicion funciones
void pasoValor (struct mi_estructura estructura_pila);

void main()
{
struct mi_estructura mia;

mia.c='1';
mia.i=10;
mia.v[1]=100;

printf("\nDireccion estructura: %p",&mia);
printf("\nDireccion campo vector en estructura: %p\n",mia.v);

pasoValor (mia);

}

void pasoValor(struct mi_estructura estructura_pila)
{

printf("\nEstructura campo 1:  %c",estructura_pila.c);
printf("\nEstructura campo 2: %i",estructura_pila.i);
printf("\nEstructura campo 3: %i\n", estructura_pila.v[1]);

printf("\nDireccion estructura en funcion: %p", &estructura_pila);
printf("\nDireccion campo vector en estructura en funcion: %p\n",estructura_pila.v);
}
