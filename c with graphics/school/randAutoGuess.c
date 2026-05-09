#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int num, ranNum;

    ranNum = (rand() % 100) + 1;
    printf("%d\n", ranNum);

    num = (rand() % 100) + 1;
    printf("%d\n", num);

    int tries = 0;

    while (ranNum != num)
    {
        num = (rand() % 100) + 1;
        tries++;
        printf("tries = %d \n", tries);
        if(ranNum == num) {
            printf("%d %d", ranNum, num);
            break;
        } 
    }

    return 0;
}