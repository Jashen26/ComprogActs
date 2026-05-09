#include<stdio.h>
#include<conio.h>

struct brw_dtls
{
    char Name_of_borrower [50];
    char Name_of_book [50];
    char Name_of_author [50];
    int Date_brwd;
    int Date_rtrn;
    int days_kept;
    int fine;
};

struct brw_dtls borrower[3];

int main()
{
    int allowed_days = 7;
    int monthdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < 3; i++)
    {   
        printf("\n-----Receipt %d-----\n", i + 1);

        printf("Enter borrower name: ");
        scanf(" %[^\n]", borrower[i].Name_of_borrower);

        printf("Enter The name of the book: ");
        scanf(" %[^\n]", borrower[i].Name_of_book);

        printf("Enter The name of the Author: ");
        scanf(" %[^\n]", borrower[i].Name_of_author);

        int valid_brwd = 0;
        while (!valid_brwd) {
            printf("Enter Date Borrowed (MMDDYY): ");
            if (scanf("%d", &borrower[i].Date_brwd) != 1) {
                printf("Error: Input contains letters. Please use numbers only.\n");
                while (getchar() != '\n');
            } else {
                int m = borrower[i].Date_brwd / 10000;
                int d = (borrower[i].Date_brwd / 100) % 100;
                if (m >= 1 && m <= 12 && d >= 1 && d <= 31) {
                    valid_brwd = 1;
                } else {
                    printf("Error: Invalid date format. (Month 01-12, Day 01-31)\n");
                }
            }
        }

        int valid_rtrn = 0;
        while (!valid_rtrn) {
            printf("Enter Date Returned (MMDDYY): ");
            if (scanf("%d", &borrower[i].Date_rtrn) != 1) {
                printf("Error: Input contains letters. Please use numbers only.\n");
                while (getchar() != '\n'); // Clear buffer
            } 
            else {
                int m = borrower[i].Date_rtrn / 10000;
                int d = (borrower[i].Date_rtrn / 100) % 100;
                if (m >= 1 && m <= 12 && d >= 1 && d <= 31) {
                    valid_rtrn = 1;
                } else {
                    printf("Error: Invalid date format.\n");
                }
            }
        }

        int day_brwd = (borrower[i].Date_brwd / 100) % 100;
        int month_brwd = borrower[i].Date_brwd / 10000;
        int year_brwd = borrower[i].Date_brwd % 100;

        int day_rtrn = (borrower[i].Date_rtrn / 100) % 100;
        int month_rtrn = borrower[i].Date_rtrn / 10000;
        int year_rtrn = borrower[i].Date_rtrn % 100;

        long days_brwd = year_brwd * 365;
        for (int j = 0; j < month_brwd - 1; j++) 
        {
            days_brwd += monthdays[j];
        }
        days_brwd += day_brwd;

        long days_rtrn = year_rtrn * 365;
        for (int j = 0; j < month_rtrn - 1; j++) 
        {
            days_rtrn += monthdays[j];
        }
        days_rtrn += day_rtrn;

        borrower[i].days_kept = (int)(days_rtrn - days_brwd);

        if (borrower[i].days_kept > allowed_days)
        {
            borrower[i].fine = (borrower[i].days_kept - allowed_days) * 100;
        }
        else
        {
            borrower[i].fine = 0;
        }

    }

   printf("\n%-30s %-30s %-30s %-10s %-10s %-6s %-6s\n", "BORROWER", "BOOK TITLE", "BOOK AUTHOR", "DAY BORROWED", "DAY RETURNED", "DAYS KEPT", "FINE");
   printf("_____________________________________________________________________________________________________________________________________\n");
    for (int i = 0; i < 3; i++) {
        printf("%-30.30s %-30.30s %-30.30s %-10d %-10d %-6d $%d\n", 
               borrower[i].Name_of_borrower, borrower[i].Name_of_book, borrower[i].Name_of_author, 
               borrower[i].Date_brwd, borrower[i].Date_rtrn, borrower[i].days_kept, borrower[i].fine);
    }

    return 0;
}