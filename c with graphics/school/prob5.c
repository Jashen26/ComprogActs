#include <stdio.h>

// inpput 2 numbers 1 and b. 
// if the average of the numbers is less than 15. Print the sum.
//if the average is equal to 15. print the difference.
// if the average is greater than 15. prnt the product.



int main () {
int num1, num2, ave;

printf("enter a number: ");
scanf("%d %d", &num1, &num2);

ave = (num1 + num2) / 2;

if (ave < 15) {
    printf("ave < 15 = %d", num1 + num2);
}
else if (ave == 15) {
    printf("ave = 15 is equal to %d", num1 - num2);
}
else {
    printf ("ave > 15 = %d", num1 * num2);
}

return 0;
}
