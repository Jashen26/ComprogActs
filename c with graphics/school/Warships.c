#include <stdio.h>

int main()
{
    char input;

    printf("choose a warship\n (B) for Battleship\n (C) for Cruiser\n (D) for destroyer\n (F) for trigate\n");
    scanf("%c", &input);

    switch (input)
    {
    case 'B':
    case 'b':
        printf("you have choosen the Battleship.");
        break;

    case 'C':
    case 'c':
        printf("you have choosen the Cruiser.");
        break;

    case 'D':
    case 'd':
        printf("you have choosen the Destroyer.");
        break;

    case 'F':
    case 'f':
        printf("you have choosen the Trigate.");
        break;

        default: printf("Not a warship.");
    }

    return 0;
}