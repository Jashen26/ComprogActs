#include <stdio.h>
#include <stdlib.h>

#define maxClient 5
struct client
{
    char name[50];
    char ocp[50];
    int cvs;
    int phone;
    char email[50];
    float income;
    int loanAmount;
};

struct client details[maxClient];

float processLoan(struct client details, float *allowedLoan, float *monthlyInterest)
{
    float salary = details.income;

    *allowedLoan = salary * 0.20;

    *monthlyInterest = *allowedLoan * 0.05;
    return salary;
}

void getUserInfo(int i)
{

    printf("Enter your Name: ");
    scanf(" %[^\n]", details[i].name);

    printf("What is your Occupation: ");
    scanf(" %[^\n]", details[i].ocp);

    do
    {
        printf("What is your civil status:\n[0] single\n[1] married\n[2] widowed\n[3] divorsed\n[4] separated\n");
        int result = scanf("%d", &details[i].cvs);
        if (result == 0)
        {
            printf("invalid input!!\n");
            while (getchar() != '\n')
                ;
            details[i].cvs = 1000000;
        }
    } while (details[i].cvs < 0 || details[i].cvs > 4);

    do
    {
        printf("Enter your phone number: ");
        int result = scanf("%d", &details[i].phone);
        if (result == 0)
        {
            printf("invalid input");
            while (getchar() != '\n')
                ;
            details[i].phone = -1;
        }
    } while (details[i].phone <= 0);

    printf("Enter your Email: ");
    scanf("%s", details[i].email);
    do
    {
        printf("what is your income: ");
        int result = scanf(" %f", &details[i].income);
        if (result == 0)
        {
            printf("Invalid input!!\n");
            while (getchar() != '\n')
                ;
            details[i].income = -1;
        }
    } while (details[i].income < 0);

    do
    {
        printf("Your loanable amount is %.2f: ", details[i].income * 0.20);
        int result = scanf("%d", &details[i].loanAmount);
        if (result == 0)
        {
            printf("Invalid input!!");
            while (getchar() != '\n')
                ;
            details[i].loanAmount = -1;
        }
        if (details[i].loanAmount > details[i].income * 0.20)
        {
            printf("You exceeded your loanable Amount!");
            while (getchar() != '\n')
                ;
            details[i].loanAmount = -1;
        }
    } while (details[i].loanAmount < 0);
}

void userInfoDisplay(char *civilStatus[], float allowedLoan, float monthlyInterest, struct client details)
{
    printf("\nClient Name: %s\n", details.name);
    printf("Client Occupation: %s\n", details.ocp);
    printf("Client Civil Status: %s\n", civilStatus[details.cvs]);
    printf("Client Phone Number: %d\n", details.phone);
    printf("Client Email: %s\n", details.email);
    printf("Client income: %.2f\n", details.income);
    printf("Client Alloweable Loan: %.2f\n", allowedLoan);
    printf("Client Monthly Interest: %.2f\n", monthlyInterest);
    printf("Client Loan Amount: %d", details.loanAmount);
}

typedef enum
{
    home,
    admin,
    client,
    exit_daw,
} currentView;

typedef enum
{
    addClient = 0,
    makePayment = 1,
    back = 2,
} clientView;

int main()
{
    int viewChecker = home, clientMenu = -1;
    int i = 0;
    float allowedLoan = 0, monthlyInterest = 0;
    char *civilStatus[] = {"Single", "Married", "Widowed", "Divorsed", "Separated"};

    while (1)
    {

        puts("-------------\n");
        printf("[1] Admin\n");
        printf("[2] Client\n");
        printf("[3] Exit\n");
        scanf("%d", &viewChecker);

        if (viewChecker == exit_daw)
        {
            puts("babay.....");
            break;
        }

        else if (viewChecker == client)
        {

            printf("[0] Add Client\n");
            printf("[1] Make Payment for Client\n");
            printf("[2] To Main Menu\n");
            scanf("%d", &clientMenu);

            if (clientMenu == addClient)
            {
                if (i < maxClient)
                {
                    getUserInfo(i);
                    processLoan(details[i], &allowedLoan, &monthlyInterest);
                    i++;
                }
                else
                {
                    printf("storage is max");
                }
            }
            else if (clientMenu == makePayment)
            {
                if (i == 0)
                {
                    printf("we have no clients yet..");
                }
                else
                {
                    printf("%s's balance is %d\n", details[i-1].name, details[i-1].loanAmount);
                    printf("how much would you like to pay?");
                    int temp = 0;
                    scanf("%d", &temp);
                    details[i-1].loanAmount = details[i-1].loanAmount - temp;
                    printf("payment successful");
                }
            }
            else if (clientMenu == back)
            {
            }
        }
        else if (viewChecker == admin)
        {
        }
        else
        {
            puts("invalid input!!");
            while (getchar() != '\n')
                ;
        }
    }

    // char filename[60];
    // snprintf(filename, sizeof(filename), "Clientfolder/%sclient.txt", details[i].name);

    // FILE *fileMaker = fopen(filename, "w");
    // if (fileMaker == NULL)
    // {
    //     printf("file failed");
    //     return 1;
    // }
    // userInfoDisplay(civilStatus, allowedLoan, monthlyInterest, details[i]);

    // fprintf(fileMaker, "%s\n", details[i].name);
    // fprintf(fileMaker, "%s", details[i].ocp);

    // fclose(fileMaker);
    return 0;
}