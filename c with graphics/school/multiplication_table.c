#include <stdio.h>

int main()
{
    int num, rep;

    printf("enter a number: ");
    scanf(" %d", &num);

    printf("how many rep? ");
    scanf(" %d", &rep);

    int clone = rep - 0;
    
    for (int i = 0 ; clone - i != 0 ; i++) {
    printf("%d \n", num * rep);
    rep--;
        
    }
    return 0;
}
