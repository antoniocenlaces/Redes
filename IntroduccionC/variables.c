#include <stdio.h>

int i=0;
int j=0;

void incrementar() {
    int j=0;
    static int k=0;

    i++;
    j++;
    k++;
    printf("i=%d, j=%d, k=%d\n", i,j,k);
}

int main() {
    incrementar();  incrementar();  incrementar();
}
