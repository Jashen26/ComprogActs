#include <stdio.h>
#include <stdlib.h>

void KOMPUTE(int *pA, int *pB, int n) {

    for (int i = 0; i < n; i++)
    {
        *(pB + i) = *(pA + i) + *(pA + i + 1);
    }
    printf("\n");
    for(int i = 0; i < n - 1; i++)
    {
        printf("pB[%d]: %d\t", i, *(pB + i));
    }
    
}


int main() {

    int n = 10, *pA, *pB;

    pA = (int*) malloc(n * sizeof(int));
    pB = (int*) malloc((n - 1) * sizeof(int));

    if(pA == NULL || pB == NULL)
    {
        printf("MEMORY ALLOCATION FAILED");
        return 1;
    }


for( int i = 0; i < n; i++) {
        while(1) {

    printf("enter a number for[%d]", i);
    if(scanf("%d", (pA + i)) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
    } else {
        break;
}
    }
}
KOMPUTE(pA, pB, n);

free(pA);
free(pB);

    return 0;
}