#include <stdio.h>
#include <math.h>

int main() {
    int x[20], y[20], z[20];
    int sum;
    char chk, repeat;

    do {
        do {
            
            for (int i = 0; i < 20; i++) {
                printf("Enter data for x[%d]: ", i);
                scanf("%d", &x[i]);
            }

            
            printf("\nData for array X: ");
            for (int i = 0; i < 20; i++) {
                printf("%d ", x[i]);
            }
            printf("\n");

            
            for (int i = 0; i < 20; i++) {
                printf("Enter data for y[%d]: ", i);
                scanf("%d", &y[i]);
            }

          
            printf("\nData for array Y: ");
            for (int i = 0; i < 20; i++) {
                printf("%d ", y[i]);
            }
            printf("\n");

            printf("\nDo you want to change your data sets? (Y/N): ");
            scanf(" %c", &chk);

        } while (chk == 'Y' || chk == 'y');

        sum = 0; 

        printf("\nData for array X: ");
        for (int i = 0; i < 20; i++) {
            printf("%d ", x[i]);
        }

       
        printf("\nData for array Y: ");
        for (int i = 0; i < 20; i++) {
            printf("%d ", y[i]);
        }

       
        printf("\nData for array Z (X * Y): ");
        for (int i = 0; i < 20; i++) {
            z[i] = x[i] * y[i];
            printf("%d ", z[i]);
            sum += z[i];
        }

        
        printf("\n\nSum of array Z: %d", sum);
        printf("\nSquare root of sum: %.2f\n", sqrt(sum));

        printf("\nDo it again? (Y/N): ");
        scanf(" %c", &repeat);

    } while (repeat == 'Y' || repeat == 'y');

    return 0;
}