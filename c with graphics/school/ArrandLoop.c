#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main() {
    
    int x[20], y[20], z[20], Rnum, sumz = 0;
    char checker, repeat;

    srand(time(NULL));

do {

    do {
        for (int i = 0; i < 20; i++) {
        Rnum = (rand() % 10) + 1;
        x[i] = Rnum;
        printf("%d ", x[i]);
        }
        printf("\n do you want this set for X? y/n \n");
        scanf(" %c", &checker);
    
    } while (checker != 'y');

    do {
        for (int i = 0; i < 20; i++) {
        Rnum = (rand() % 10) + 1;
        y[i] = Rnum;
        printf("%d ", y[i]);
        }

        printf("\n do you want this set for Y? y/n \n");
        scanf(" %c", &checker);
    
    } while (checker != 'y');

    //get the product of x and y

        for (int i = 0; i < 20; i++) {
            z[i] = x[i] * y[i];

            printf("%d ", z[i]);
        }
        
        for(int j = 0; j < 20; j++) {
            sumz += z[j];
        }

        printf("\nthe sum of the array z : %d \n", sumz);
        double result = sqrt(sumz);
        printf("the squared root: %.2f", result);
    

        printf("\ndo it again?");
        scanf(" %c", &repeat);
} while (repeat == 'y' || repeat == 'Y');
    printf("program end buhbye....");

    return 0;
}