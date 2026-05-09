#include <stdio.h>
#include <string.h>
#define Maxlengstring 5 //column
#define Maxstringleng 10 //rows inside the column
//student data entry program
//should have a menu to very student
//should use function


//arrName[length of the array] [length of the string]


int main() {
    char arrName[Maxlengstring][Maxstringleng];
    
    for (int i = 0; i < Maxlengstring; i++) {
        printf("Enter a String %d:", i+1);
        fgets(arrName[i], Maxstringleng, stdin);

        int length = strlen(arrName[i]);
       if  (arrName[i][length - 1] == '\n')
       {
        arrName[i][length - 1] = '\0';
       }
       else
       {
        int c;
        while( (c = getchar()) != '\n' && c != EOF) {}
        

       }
    }

    for (int i = 0; i < Maxlengstring; i++ ) {
        printf("string %d: %s\n", i+1, arrName[i]);
    }


    return 0;
}