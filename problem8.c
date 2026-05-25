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
    float loanAmount;
    float initialLoan;
};

struct client details[maxClient];
struct client acceptClient[maxClient];
int pending = 0;
int accepted = 0;

void getUserInfo(int i)
{
    float initialLoan;

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
        int result = scanf("%f", &initialLoan);
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
            details[i].initialLoan = initialLoan;
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
    float monthlyInterest = details[i].initialLoan * 0.05;

    printf("Client Alloweable Loan: %.2f\n", allowedLoan);
    printf("Client Monthly Interest: %.2f\n", monthlyInterest);
    printf("Client Loan Amount: %.2f", details[i].loanAmount);
}

void userInfoAccepted(char *civilStatus[], struct client acceptClient[], int i)
{
    printf("\nClient Name: %s\n", acceptClient[i].name);
    printf("Client Occupation: %s\n", acceptClient[i].ocp);
    printf("Client Civil Status: %s\n", civilStatus[acceptClient[i].cvs]);
    printf("Client Phone Number: %d\n", acceptClient[i].phone);
    printf("Client Email: %s\n", acceptClient[i].email);
    printf("Client income: %.2f\n", acceptClient[i].income);

    float allowedLoan = acceptClient[i].income * 0.20;
    float monthlyInterest = acceptClient[i].initialLoan * 0.05;

    printf("Client Alloweable Loan: %.2f\n", allowedLoan);
    printf("Client Monthly Interest: %.2f\n", monthlyInterest);
    printf("Client Loan Amount: %.2f", acceptClient[i].loanAmount);
}

void makePayment()
{
    if (accepted == 0)
    {
        printf("\nThere are no Clients in the system.\n");

        return;
    }

    printf("Select a Client");
    for (int i = 0; i < accepted; i++)
    {
        printf("\n[%d] %s\n", i + 1, acceptClient[i].name);
    }

    int choice;
    printf("Enter client number: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > accepted)
    {
        printf("Invalid selection!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    int targetclient = choice - 1;

    printf("\n%s's current loan balance is: $%.2f\n", acceptClient[targetclient].name, acceptClient[targetclient].loanAmount);

    if (acceptClient[targetclient].loanAmount <= 0)
    {
        printf("This client has no remaining balance to pay!\n");
        return;
    }

    float payment;
    printf("Enter payment amount: ");
    if (scanf("%f", &payment) != 1 || payment <= 0)
    {
        printf("Invalid payment amount!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (payment > acceptClient[targetclient].loanAmount)
    {
        printf("Payment exceeds balance! Adjusting payment to match remaining balance ($%.2f).\n", acceptClient[targetclient].loanAmount);
        payment = acceptClient[targetclient].loanAmount;
    }

    acceptClient[targetclient].loanAmount -= payment;
    printf("Payment successful! New balance for %s: $%.2f\n", acceptClient[targetclient].name, acceptClient[targetclient].loanAmount);
    char filename[60];
    snprintf(filename, sizeof(filename), "Clientfolder/%sclient.txt", acceptClient[accepted - 1].name);

    FILE *fileMaker = fopen(filename, "w");
    if (fileMaker == NULL)
    {
        printf("file failed");
        return;
    }
    // fprintf(fileMaker, "%d", accepted);
    // fprintf(fileMaker, "Client's order Number: %d ", accepted);
    fprintf(fileMaker, "Client's Name:%s\n", acceptClient[accepted - 1].name);
    fprintf(fileMaker, "Balance: %.2f\n", acceptClient[accepted - 1].loanAmount);
    fclose(fileMaker);
}

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
            return;
        case 2:
            makePayment();
            return;
        case 3:
            return;
        default:
            puts("Invalid Input!");
        }
    }
}

void viewPendingClient(char *civilStatus[])
{

    int checker = 0;
    int choice = 0;
    while (1)
    {
        if (pending == 0)
        {
            puts("we have no Pending Clients!!");
            return;
        }

        puts("------Choose which client to Entertain----------");
        for (int j = 0; j < pending; j++)
        {
            printf("[%d] %s\n", j + 1, details[j].name);
        }
        printf("0 to back in main menu\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid INPUT!!\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (choice == 0)
        {
            return;
        }

        int clientNumber = choice - 1;

        if (choice >= 1 && choice <= pending)
        {
            userInfoDisplay(civilStatus, details, clientNumber);
            printf("\n[1] Accept\n[2] Decline");
            scanf("%d", &checker);
        }

        switch (checker)
        {
        case 1:
            acceptClient[accepted] = details[clientNumber];
            printf("Accept Successful");
            accepted++;

            char filename[60];
            snprintf(filename, sizeof(filename), "Clientfolder/%sclient.txt", acceptClient[accepted - 1].name);

            FILE *fileMaker = fopen(filename, "w");
            if (fileMaker == NULL)
            {
                printf("file failed");
                return;
            }
            // fprintf(fileMaker, "Client's order Number: %d ", accepted);
            fprintf(fileMaker, "Client's Name:%s\n", acceptClient[accepted - 1].name);
            fprintf(fileMaker, "Balance: %.2f\n", acceptClient[accepted - 1].loanAmount);
            fclose(fileMaker);

            for (int i = clientNumber; i < pending - 1; i++)
            {
                details[i] = details[i + 1];
            }
            pending--;

            return;
        case 2:
            for (int i = clientNumber; i < pending - 1; i++)
            {
                details[i] = details[i + 1];
            }

            pending--;
            return;

        default:
            printf("Invalid Input!");
        }
    }
}
void viewClients(char *civilStatus[])
{
    if (accepted > 0)
    {
        for (int i = 0; i < accepted; i++)
        {
            printf("client[%d]", i + 1);
            userInfoAccepted(civilStatus, acceptClient, i);
        }
    }
    else
    {
        printf("we have no clients yet\n");
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
        case 1:
            viewPendingClient(civilStatus);
            return;
        case 2:
            viewClients(civilStatus);
            return;
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

    // FILE *fileLoader = fopen("DataBase", "r");
    // if (fileLoader == NULL)
    // {
    //     printf("file failed");
    //     return 0;
    // }
    //     fscanf(fileLoader, "Client's order Number: %d ", accepted);
    // for (int i = 0; i < accepted; i++)
    // {
    //     fscanf(fileLoader, "Client's Name:%s\n", &acceptClient[accepted - 1].name);
    //     fscanf(fileLoader, "Balance: %.2f\n\n", &acceptClient[accepted - 1].loanAmount);
    // }
    // fclose(fileLoader);

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
    return 0;
}