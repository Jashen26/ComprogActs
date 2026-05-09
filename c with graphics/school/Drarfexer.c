#include <stdio.h>

void DWARF(int num, int sum)
{
    printf("\nInputed Number: %d ", num);

    printf("\nFactors are: ");

    // factor and sum
    for (int i = 1; i < num; i++)
    {
        if (num % i == 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nsum of the factor: %d", sum);

    // number half
    float numhalf = num / 2.00;
    printf("\nhalf of the number: %.2lf", numhalf);

    // dwaft or not

    if (numhalf < sum)
    {
        printf("\n%d is a DWARF", num);
    }
    else
    {
        printf("\n%d is not a DWARF", num);
    }
}

int main()
{
    int num, sum = 0;
    // check for non negative integers
    do
    {
        printf("enter a Non-negative Interger: ");
        scanf(" %d", &num);
    } while (num <= 0);

    DWARF(num, sum);
    return 0;
}