#include <stdio.h>

// input 2 number and determine the largest number.

int main () {
    double ft, in, meter, cm;
printf("enter a number: ");
scanf("%lf", &ft);

in = ft * 12;
cm = in * 2.57;
meter = cm / 100;

printf("ft to in: %.2lf\n", in);
printf("ft to meter: %.2lf\n", meter);
printf("ft to cm: %.2lf\n", cm);

return 0;
}