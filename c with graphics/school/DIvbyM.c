#include<stdio.h>
#include<math.h>

//divisible by M

int main() {
    int N1, N2, M, i;
    int count = 0; 
    char choice;
    do
    {
        printf("\nEnter Value of N1: ");
        scanf("%d", &N1);

        printf("\nEnter Value of N2: ");
        scanf("%d", &N2);

        printf("\nEnter Value of M: ");
        scanf("%d", &M);

        printf("\nWould you like to change any values (Y/N) ?: ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    
    printf("\nThese are the numbers that are divisible by %d between %d and %d\n", M, N1, N2);

        for (i = N1; i <=N2; i++)
            if (i % M == 0){
            printf("%d ", i);
            count++;
        }
    
    

    printf("\nThere are %d numbers that are divisible by %d", count, M);

    return 0;
}