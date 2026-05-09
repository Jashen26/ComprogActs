#include <stdio.h>

// input 2 number and determine the largest number.



int main () {
double hours, c, b, t;
char type;

printf("what type and hours: ");
scanf("%c %lf", &type, &hours);

if (type == 'c') {
    printf("type car rate 25 per hours\ntotal: %.2lf", hours * 25);
}
else if (type == 'b') {
    printf("type bus rate 50 pe hour\ntotal: %.2lf", hours * 50);
}
else if (type == 't') {
        printf("type truck rate 75 per hour\ntotal: %.2lf", hours * 75);
}
else {
    printf("invalid input");
}

return 0;
}
