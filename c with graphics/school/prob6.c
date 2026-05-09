#include <stdio.h>

//input  any number and determine if it is divisible by 5, display invalid inputs.


int main () {
int num, result;

printf("enter a number: ");
result = scanf("%d", &num);

// printf("results returns: %d ", result); //for understanding

if (result == 1) {
    if (num % 5 == 0) {
        printf("your number %d is divisible by 5", num);
    }
    else {
        printf("invalid input.");
    }
}
else {
    printf("invalid input");
}

return 0;

}
