#include <stdio.h>

int main()
{

    char name[20];
    double years, months, days, seconds;

    printf("please inout the name of the dinosaur: ");
    scanf("%s", name); 
    
    printf("please inout the years ago it lives: ");
    scanf("%lf", &years);

    months = years * 12;
    days = years * 365.25;
    seconds = days * 24 * 60 * 60;

    printf("%s lives for %.2lf\n", name, years);
    printf("that is  %.2lf months ago\n", months);
    printf("this is %.2lf days ago\n", days);
    printf("this is %.2lf seconds ago\n", seconds); 
    
    return 0;
}