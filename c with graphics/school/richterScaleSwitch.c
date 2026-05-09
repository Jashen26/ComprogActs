#include <stdio.h>

int main() {
    float N;
    int level;

    printf("Enter the Richter scale value: ");
    scanf("%f", &N);

    if (N < 5.0)
        level = 0;
    else if (N >= 5.0 && N < 5.5)
        level = 1;
    else if (N >= 5.5 && N < 6.5)
        level = 2;
    else if (N >= 6.5 && N < 7.5)
        level = 3;
    else 
        level = 4;

    switch (level) {
        case 0:
            printf("LITTLE OR NO DAMAGE\n");
            break;
        case 1:
            printf("THERE ARE SOME DAMAGES\n");
            break;
        case 2:
            printf("THERE ARE SERIOUS DAMAGE!\n");
            break;
        case 3:
            printf("DISASTER! HOUSE AND BUILDINGS MAY COLLAPSE!\n");
            break;
        case 4:
            printf("CATASTROPE!\n");
            break;
    }

    return 0;
}