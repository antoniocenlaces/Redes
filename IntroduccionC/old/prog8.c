#include <stdio.h>

void intercambia( x, y )
int x, y;
{
  int tmp;

  tmp = x;
  x = y;
  y = tmp;
}

main()
{

  void intercambia();
  int a = 1, b = 2;

  intercambia( a, b );
  printf( "\n\ta = %d\tb = %d\n", a, b );

}
