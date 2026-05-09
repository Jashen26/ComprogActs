#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
int month, days, year = 26, maxday;

struct user_detail
{
    char borrowerName[50];
    char bookTitle[50];
    char authorName[50];
    int dateBorrowed;
    int dateReturn;
};
struct user_detail userInfo;

void getUserInfo(struct user_detail *userInfo)
{
    printf("Enter Borrower Name: ");
    fgets(userInfo->borrowerName, 50, stdin);
    userInfo->borrowerName[strcspn(userInfo->borrowerName, "\n")] = 0;

    printf("Enter Book Title: ");
    fgets(userInfo->bookTitle, 50, stdin);
    userInfo->bookTitle[strcspn(userInfo->bookTitle, "\n")] = 0;

    printf("Enter Author Name: ");
    fgets(userInfo->authorName, 50, stdin);
    userInfo->authorName[strcspn(userInfo->authorName, "\n")] = 0;

    do
    {
        printf("Enter Date borrowed (MMDD26): ");
        int result = (scanf("%d", &userInfo->dateBorrowed));
        if (result != 1)
        {
            while (getchar() != '\n');
            continue;
        }

        month = userInfo->dateBorrowed / 100;
        days = userInfo->dateBorrowed % 100;
        maxday = 0;
        if (month == 2)
        {
            maxday = 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            maxday = 30;
        }
        else
        {
            maxday = 31;
        }

        if (month < 1 || month > 12 || days < 1 || days > maxday)
        {
            printf("invalid date! pls enter a valid one: ");
        }
        else
        {
            break;
        }

    } while (1);
}

// void printInfo(struct user_detail *userInfo)
// {
//     printf("%s\n", userInfo->borrowerName);
//     printf("%s\n", userInfo->bookTitle);
//     printf("%s\n", userInfo->authorName);
//     printf("%d\n", userInfo->dateBorrowed);
// }

int main()
{
    int fine = 0, day = 1, dayKept = 0, overDue = 0;
    
    char checker = 'n';
    char *monthList[] = {"Invalid", "January", "February", "March", "April", "May", "June",
                         "July", "August", "September", "October", "November", "December"};

    
     
    getUserInfo(&userInfo);
    int tempday = days;
    int tempYear = year;
    // printInfo(&userInfo);
    while (1)
    {
        printf("Day %d\n", day);
        printf("do you want to pay now? (y/n): ");
        scanf(" %c", &checker);
        if (checker == 'n')
        {
            day++;
            tempday++;
            dayKept++;
            if (day > 8)
            {
                fine += 50;
                overDue++;
            }

            if (tempday == maxday)
            {
                month++;
                tempday = 1;
                if (month > 12)
                {
                    month = 1;
                    tempYear++;
                }
            }
        }
        else if (checker == 'y')
        {
            printf("\n%-30s %-30s %-30s %-27s %-20s %-10s %-10s %-10s\n", "BorrowerBook", "titleBook", "AuthorName", "BorrowedDate", "ReturnedDate", "Fine", "Dayskept", "Overdue");
            printf("\n%-30s %-30s %-30s %-2s %-2d %-16d %-2s %-2d %-10d %-10d %-10d %-10d",userInfo.borrowerName, userInfo.bookTitle, userInfo.authorName, monthList[month], days, year, monthList[month], tempday, tempYear, fine, dayKept, overDue);
            break;
        }
        else
        {
            printf("invalid input!");
        }
    }



    return 0;
}
