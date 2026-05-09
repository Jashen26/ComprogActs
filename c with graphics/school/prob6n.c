#include <stdio.h>

// input 2 number and determine the largest number.



int main () {
int num;

printf("enter a number");
scanf("%d", num);

if (num % 5 == 0) {
    printf("your number is div by 5");
}
else if (num % 5 == 1) {
    printf("your number is not div by 5");
}
else {
    printf("invalid input");
}
return 0;
}
