#include <stdio.h>

// jedi passed or not



int main () {
int height, age, citizen, rec;

printf("what is your height: ");
scanf("%d", &height);

printf("how old: ");
scanf("%d", &age);

printf("Are you a citizen?\n (1) yes\n (0) no\n");
scanf("%d", &citizen);

printf("Are you recommended?\n (1) yes\n (0) no\n");
scanf("%d", &rec);

if (citizen == 1) {
    printf("you passed");
}
else if(height >= 200 && age >= 21 && age <= 25 && citizen == 1 ) {
    printf("you passed");
}
else {
    printf("Failed");
}
return 0;
}
