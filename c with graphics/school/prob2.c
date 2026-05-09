#include <stdio.h>

// inout any number and determine if it is positive or negative. print the number and indicate its sign



int main () {
int num = 0;

printf("enter a number: ");
scanf("%d", &num);

if (num > 0) {
    printf("the number %d is a positive", num);
}
else {
    printf("the number %d is a negative", num);
}

return 0;
}
