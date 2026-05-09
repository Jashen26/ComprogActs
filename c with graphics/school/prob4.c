#include <stdio.h>

// input any number and tell if its an odd or even



int main () {
int num;

printf("enter a number: ");
scanf("%d", &num);

if (num % 2 == 0 ) {
    printf("your number %d is even", num);
}
else {
    printf("your number is odd");
}
return 0;
}
