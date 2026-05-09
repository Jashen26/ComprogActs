#include <stdio.h>

// input any number and determine if its a divisible by 5.



int main () {
int num;

printf("enter a number: ");
scanf("%d", &num);

if (num % 5 == 0) {
    printf("the number %d is a divisible by 5", num);
}
else {
    printf("your number is not divisible by 5");
}
return 0;
}
