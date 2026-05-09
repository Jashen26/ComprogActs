#include <stdio.h>

//jedi

int main(){
    int cm = 0, age = 0;
    char code;

printf("Are you a recommendee of jedi master Obi Wan: \n(1) if yes and (0) if no\n");
scanf(" %c", &code);

if (code == '1')
{printf("Congratulations you are ACCEPTED into the academy");}

else if(code == '0')
{printf("are you a citizen of planet Endor: \n(1) if yes and (0) if no\n");
scanf(" %c", &code);


if (code == '0')
{printf("You are REJECTED from the academy\n");}

else if (code == '1')

{printf("How tall are you: \n");
scanf("%d", &cm);

if (cm < 200)

{printf("You are REJECTED from the academy\n");}

else if (cm >= 200)
{printf("How old are you: \n");
scanf("%d", &age);

if (age < 21 || age > 25)
{printf("you are REJECTED from the academy\n");
}

else if( age >= 21 && age <= 25)
{printf("Congratulations you are ACCEPTED into the academy\n");}

}
}
}
return 0;
}