#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    int *a, b = 5;

    a = malloc(b * sizeof(int));

    for(int i = 0; i < b; i++) {
        printf("enter a number: ");
        scanf("%d", a + i);
    }
    int temp = *(a + 0);
    *(a+0)=*(a+4);
    *(a+4) = temp;

    int red = *(a + 1);
    *(a+1)=*(a+3);
    *(a+3) = red;

    for(int i = 0; i < b; i++) {
        printf("%d ", *(a + i));
    }
    return 0;
}