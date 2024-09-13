#include<stdio.h>

int main()
{
  int j = 5;
  char ch;

  printf( "\nIntro. un caracter: " );
  ch = getc(stdin);

  printf( "\n\tEl codigo de %c es %d", ch, ch );

  ch += j;

  printf( "\n\tEl codigo de %c es %d\n", ch, ch );

}
