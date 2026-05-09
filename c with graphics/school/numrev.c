#include <stdio.h>
int main() {
   
   int num, rev=0;

   printf("enter a number: ");
   scanf("%d", &num);

   while(num != 0) {
    int lastdigit = num % 10;
    rev = rev * 10 + lastdigit;
    num = num / 10;
   }
   printf("print : %d", rev);

    return 0;
}