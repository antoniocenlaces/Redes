#include <stdio.h>

void intercambia(int x, int y)
{
  int tmp;

  tmp = x;
  x = y;
  y = tmp;
}

int main()
{
  int a = 1, b = 2;

  intercambia( a, b );
  printf( "\n\ta = %d\tb = %d\n\n", a, b );
}
