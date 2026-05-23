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
struct client acceptClient[maxClient];
int pending = 0;
int accepted = 0;

void getUserInfo(int i)
{
    int initialLoan;

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
        int result = scanf("%d", &initialLoan);
        if (result == 0)
        {
            printf("Invalid input!!");
            while (getchar() != '\n')
                ;
            initialLoan = -1;
        }
        else if (initialLoan > details[i].income * 0.20)
        {
            printf("You exceeded your loanable Amount!");
            initialLoan = -1;
        }
        else
        {
            details[i].loanAmount = initialLoan + (initialLoan * 0.05);
        }

    } while (initialLoan < 0);
}

void userInfoDisplay(char *civilStatus[], struct client details[], int i)
{
    printf("\nClient Name: %s\n", details[i].name);
    printf("Client Occupation: %s\n", details[i].ocp);
    printf("Client Civil Status: %s\n", civilStatus[details[i].cvs]);
    printf("Client Phone Number: %d\n", details[i].phone);
    printf("Client Email: %s\n", details[i].email);
    printf("Client income: %.2f\n", details[i].income);

    float allowedLoan = details[i].income * 0.20;
    float monthlyInterest = allowedLoan * 0.05;

    printf("Client Alloweable Loan: %.2f\n", allowedLoan);
    printf("Client Monthly Interest: %.2f\n", monthlyInterest);
    printf("Client Loan Amount: %d", details[i].loanAmount);
}


void userInfoAccepted(char *civilStatus[], struct client acceptClient[],int i)
{
    printf("\nClient Name: %s\n", acceptClient[i].name);
    printf("Client Occupation: %s\n", acceptClient[i].ocp);
    printf("Client Civil Status: %s\n", civilStatus[acceptClient[i].cvs]);
    printf("Client Phone Number: %d\n", acceptClient[i].phone);
    printf("Client Email: %s\n", acceptClient[i].email);
    printf("Client income: %.2f\n", acceptClient[i].income);

    float allowedLoan = acceptClient[i].income * 0.20;
    float monthlyInterest = allowedLoan * 0.05;

    printf("Client Alloweable Loan: %.2f\n", allowedLoan);
    printf("Client Monthly Interest: %.2f\n", monthlyInterest);
    printf("Client Loan Amount: %d", acceptClient[i].loanAmount);
}



// void makePayment()
// {

//     printf("%s's balance is %.2f", details[pending].name, details[pendi].loanAmount);
// }

void clientMenu()
{
    int Checker = 0;

    while (1)
    {
        puts("-----------Client's Menu");
        printf("[1] Add Client\n");
        printf("[2] Make Payment for Client\n");
        printf("[3] To Main Menu\n");
        int result = scanf("%d", &Checker);

        if (result != 1)
        {
            while (getchar() != '\n')
                ;
        }

        switch (Checker)
        {
        case 1:
            getUserInfo(pending);
            pending++;
            break;
        case 2:
            // makePayment();
            break;
        case 3:
            return;
        default:
            puts("Invalid Input!");
        }
    }
}

void viewPendingClient(char *civilStatus[])
{

    int checker = 0; int i = 0;
    while(1) {
        if (pending == 0) {
            puts("we have no Pending Clients!!");
        }
        if (pending < maxClient) {
            userInfoDisplay(civilStatus,details,i);
            printf("[1] Accept\n[2] Decline");
            scanf("%d", &checker);
        }
        switch(checker) {
            case 1: acceptClient[pending] = details[pending];
                    printf("Accept Successful");
                    accepted++;
                    break;
            case 2: pending = 0;
                    break;
        }


    }

}

void viewClients(char *civilStatus[])
{
    for( int i = 0; i < accepted; i++ ) {
        userInfoAccepted(civilStatus,acceptClient,i);
    }
}

void deleteClient()
{
}

void adminMenu(char *civilStatus[])
{
    int adminChecker = 0;

    while (1)
    {

        puts("-------------Admin's Menu---------------");
        printf("[1] View Pending Clients\n");
        printf("[2] View Current Client\n");
        printf("[3] Delete a Client\n");
        int result = scanf("%d", &adminChecker);

        if (result != 1)
        {
            while (getchar() != '\n')
                ;
        }

        switch (adminChecker)
        {
        case 1:viewPendingClient(civilStatus);
             break;
        case 2:
            viewClients(civilStatus);
            break;
        case 3:
               deleteClient(); 
            return;
        default:
            puts("Invalid Input!");
        }
    }
}

int main()
{
    int mainChecker = 0;
    char *civilStatus[] = {"Single", "Married", "Widowed", "Divorsed", "Separated"};
    while (1)
    {
        puts("\n----- Main Menu");
        printf("[1] Client System\n");
        printf("[2] Admin System\n");
        printf("[3] Exit\n");
        scanf("%d", &mainChecker);

        if (mainChecker == 1)
        {
            clientMenu();
        }
        else if (mainChecker == 2)
        {
            adminMenu(civilStatus);
        }
        else if (mainChecker == 3)
        {
            break;
        }
        else
        {
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
    // userInfoDisplay(civilStatus, details[i]);

    // fprintf(fileMaker, "%s\n", details[i].name);
    // fprintf(fileMaker, "%s", details[i].ocp);

    // fclose(fileMaker);
    return 0;
}