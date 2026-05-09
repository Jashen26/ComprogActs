#include <stdio.h>

// input 2 number and determine the largest number.



int main () {
int num1, num2;

printf("enter a number: ");
scanf("%d %d", &num1, &num2);

if (num1 > num2 ) {
    printf("%d is less than %d", num2, num1);
}
else if (num1 < num2) {
    printf("%d is greater than %d",num2, num1 );
}
else if (num1 == num2) {
    printf("both numbers are equal");
}
else ("invalid input");

return 0;
}
