#include<stdio.h>

int Military_Time(int time)
{
    int hours = time / 100, minutes = time % 100;

    char *nightday;

     if (hours > 24 || minutes > 59 || hours < 0 || minutes < 0 || (hours == 24 && minutes != 0))  
    {
        printf("Invalid Input!!!\n");
        return 0;
    }

    if (hours >= 12 && hours != 24) 
    {
        nightday = "PM";
    }
    else
    {
        nightday = "AM";
    }

    hours = hours % 12; 

    if(hours == 0)
    {
        hours = 12;
    }


    printf("%d:%02d %s\n", hours, minutes, nightday); 

    return 1;
}

int main()
{
    int time;

    while(1)
    {
    printf("Please enter the time you want to conver (0000 - 2400): ");

    if (scanf("%d", &time) !=1)
    {
        printf("INVALID INPUT!!! Please input numbers only \n");

        while(getchar() != '\n');

        continue;
    }
    if (Military_Time(time))
    {
        break;
    }

    }   


    return 0;
}