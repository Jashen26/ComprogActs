#include <stdio.h>
#include <string.h>

int main()
{
    char user[50];
    int bal = 0, num = 0;

    while (strcmp(user, "exit") != 0)
    {
        printf("\ncheck, deposit, withdraw, exit ");
        printf("what do you want to ");
        scanf("%s", &user);

       if (strcmp(user,"check") == 0) {
        printf("your current balance is %d", bal);
       }
        else if (strcmp(user,"deposit") == 0) {

            printf("how much: ");
            scanf(" %d", &num);
            bal += num;
            printf(" your current balance is now %d", bal);
        }
        else if (strcmp(user, "withdraw") == 0) {
            printf("how much?");
            scanf("%d", &num);
            bal = bal - num;
            printf("your current balance now is %d", bal);
        }
        else {
            printf("Invalid Input");
        }
       }
    return 0;
}