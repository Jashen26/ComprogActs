#include <stdio.h>

int main () {
double pound, jupiter, mars;

printf("enter pound: ");
scanf("%lf", &pound);

mars = pound * 0.38;
jupiter = pound * 2.64;

printf("%.2lf pounds in mars\n", mars);
printf("%.2lf pounds in jupiter", jupiter);
return 0;
}
