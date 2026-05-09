#include <stdio.h>

int main() {
    char name[50];
    int answer, total = 0;
    float avg;

    printf("Enter student name: ");
    scanf("%s", name);


    printf("Enter Answer #1? ");
    scanf("%d", &answer);

    if (answer == 1)
        total += 1;
    else if (answer == 2)
        total += 2;
    else if (answer == 3)
        total += 3;
    else if (answer == 4)
        total += 4;
    else if (answer == 5)
        total += 5;
    else
        printf("OUT OF RANGE!\n");

    
    printf("Enter Answer #2? ");
    scanf("%d", &answer);

    if (answer == 1)
        total += 1;
    else if (answer == 2)
        total += 2;
    else if (answer == 3)
        total += 3;
    else if (answer == 4)
        total += 4;
    else if (answer == 5)
        total += 5;
    else
        printf("OUT OF RANGE!\n");



    printf("Enter Answer #3? ");
    scanf("%d", &answer);

    if (answer == 1)
        total += 1;
    else if (answer == 2)
        total += 2;
    else if (answer == 3)
        total += 3;
    else if (answer == 4)
        total += 4;
    else if (answer == 5)
        total += 5;
    else
        printf("OUT OF RANGE!\n");

    
    printf("Enter Answer #4? ");
    scanf("%d", &answer);

    if (answer == 1)
        total += 1;
    else if (answer == 2)
        total += 2;
    else if (answer == 3)
        total += 3;
    else if (answer == 4)
        total += 4;
    else if (answer == 5)
        total += 5;
    else
        printf("OUT OF RANGE!\n");


    printf("Enter Answer #5? ");
    scanf("%d", &answer);

    if (answer == 1)
        total += 1;
    else if (answer == 2)
        total += 2;
    else if (answer == 3)
        total += 3;
    else if (answer == 4)
        total += 4;
    else if (answer == 5)
        total += 5;
    else
        printf("OUT OF RANGE!\n");

    
    avg = total / 5.0;
    printf("%s, your total score is %d and your average score is %.1f.\n",
           name, total, avg);

    return 0;
}