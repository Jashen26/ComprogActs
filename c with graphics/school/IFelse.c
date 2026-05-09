#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int number, totNum = 0, numArr[10];

    for (int i = 0; i < 10; i++)
    {

        numArr[i] = (rand() % 100) + 1;

        printf("%d ", numArr[i]);

        int temp = 0;
        if ((i + 1) % 3 == 0)

            temp = numArr[i];
            totNum += temp;
        printf("%d", temp);
        printf("\n");
    }


    printf("%d", totNum);

    return 0;
}