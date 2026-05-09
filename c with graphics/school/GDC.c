#include<stdio.h>
#include<math.h>

int main(){
    int x, y;
    int gcd;
    char choice, repeat;

    do {
        do{
        printf("\nEnter the value of the first Non-negative number: ");
        scanf("%d", &x);

        printf("\nEnter the value of the second Non-negative number: ");
        scanf("%d", &y);

        printf("\nWould you like to change values (Y/N)?: ");
        scanf(" %c", &choice);
    } while(choice == 'Y' || choice == 'y');

    for (int i = 1; i <=x && i <= y; i++){
        if (x % i == 0 && y % i == 0){
            gcd = i;
        }
    }
    printf("\nGreatest Common Divisor is %d\n", gcd);

    printf("\nWould you like to do it again (Y/N)?: ");
    scanf(" %c", &repeat);
    
    } while (repeat == 'Y' || repeat == 'y');


    printf("\nProgram Terminated");

    return 0;
}