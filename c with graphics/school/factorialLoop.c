#include <stdio.h>

int main()
{

    int num;
    int sum = 0;
    printf("enter a number to see its factorial: ");
    scanf("%d", &num);

    while (num >= 1)
    {
        printf(" %d", num);
        sum += num;
        num--;
        }
    printf(" %d\n", sum);
    return 0;
}