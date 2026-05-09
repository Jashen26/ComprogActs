#include <stdio.h>

int main() {
    int num;
    double sum;
    char choice;
    
    do {
        sum = 0.0;
        
        printf("Enter a number (less than 100): ");
        scanf("%d", &num);
        
        // Validate input
        if (num >= 100) {
            printf("Number must be less than 100!\n");
            printf("\nDo you want to try again? (y/n): ");
            scanf(" %c", &choice);
            continue;
        }
        
        // Calculate sum of cube roots of every second integer
        printf("\nCalculating: ");
        for (int i = num + 1; i < 100; i += 2) {
            // Calculate cube root using Newton-Raphson method inline
            double n = (double)i;
            double x = n;
            double precision = 0.000001;
            double x_new;
            
            // Newton-Raphson: x_new = (2*x + n/x^2) / 3
            do {
                x_new = (2.0 * x + n / (x * x)) / 3.0;
                if (x > x_new) {
                    if (x - x_new < precision)
                        break;
                } else {
                    if (x_new - x < precision)
                        break;
                }
                x = x_new;
            } while (1);
            
            sum += x_new;
            printf("cbrt(%d) ", i);
            if (i + 2 <= num) printf("+ ");
        }
        
        printf("\n\nSum of cube roots of every second integer up to %d: %.4f\n", num, sum);
        
        printf("\nDo you want to calculate again? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("Program terminated. Goodbye!\n");
    
    return 0;
}