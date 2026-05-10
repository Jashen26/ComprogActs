#include <stdio.h>
#include <stdlib.h>

struct client
{
    char name[50];
    char ocp[50];
    int cvs;
    int phone;
    char email[50];
    float income;
};

struct client details;

float processLoan(struct client details, float *allowedLoan ,float *monthlyInterest )
{
    float salary = details.income;

    *allowedLoan = salary * 0.20;

    *monthlyInterest = *allowedLoan * 0.05;
    return salary;
}

void getUserInfo()
{
    printf("Enter your Name: ");
    scanf("%[^\n]", details.name);
    printf("What is your Occupation: ");
    scanf(" %[^\n]", details.ocp);
    do
    {
        printf("What is your civil status:\n[0] single\n[1] married\n[2] widowed\n[3] divorsed\n[4] separated\n");
        int result = scanf("%d", &details.cvs);
        if (result == 0)
        {
            printf("invalid input!!\n");
            while (getchar() != '\n')
                ;
            details.cvs = 1000000;
        }
    } while (details.cvs < 0 || details.cvs > 4);

    do {
        printf("Enter your phone number: ");
        int result = scanf("%d", &details.phone);
        if(result == 0) {
            printf("invalid input");
            while(getchar() != '\n');
            details.phone = -1;
        }
    }while(details.phone <= 0);


    printf("Enter your Email: ");
    scanf("%s", details.email);
    do
    {
        printf("what is your income: ");
        int result = scanf(" %f", &details.income);
        if(result == 0) {
            printf("Invalid input!!\n");
            while(getchar() != '\n');
            details.income = -1;
        }
    } while (details.income < 0);
}

void userInfoDisplay(char *civilStatus[], float allowedLoan, float monthlyInterest, struct client details) {
     printf("\nClient Name: %s\n", details.name);
    printf("Client Occupation: %s\n", details.ocp);
    printf("Client Civil Status: %s\n", civilStatus[details.cvs]);
    printf("Client Phone Number: %d\n", details.phone);
    printf("Client Email: %s\n", details.email);
    printf("Client income: %.2f\n", details.income);
    printf("Client Alloweable Loan: %.2f\n", allowedLoan);
    printf("Client Monthly Interest: %.2f\n", monthlyInterest);
}

int main()
{
    float allowedLoan = 0, monthlyInterest = 0;
    char *civilStatus[] = {"Single", "Married", "Widowed", "Divorsed", "Separated"};
    getUserInfo();
    processLoan(details, &allowedLoan, &monthlyInterest);
    userInfoDisplay(civilStatus, allowedLoan, monthlyInterest, details);
    return 0;
}