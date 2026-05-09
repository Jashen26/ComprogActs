#include <stdio.h>

// compute the area of a rectangle and the area of a triagle



int main () {
int h ,w , Arec, Atri;
char input;

printf("enter r for rectangle\nenter t for triangle: ");
scanf("%c", &input);

printf("write the height and width: ");
scanf("%d %d", &h, &w);

Arec = h * w;
Atri = h * w / 2;

switch (input) {
    case 'r' : 
    case 'R' :
    printf("the total are of the rectangle is %d", Arec);
    break;

    case 't':
    case 'T':
    printf("the total area of the triangle is %d", Atri);
    break;
}
 

return 0;
}
