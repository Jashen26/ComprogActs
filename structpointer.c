#include <stdio.h>
#include <stdlib.h>


// struct structName *pointer to structure variable 

struct record
{
    char name[90];
    int age;
};

struct record buddy, *pointbuddy;

pointbuddy = &buddy;

//*pointbuddy = actual value + 3
// *(pointbuddy) = index + 3

struct recordx {
    char name2[23];
};

struct recordx ptx;

void fucntionName(struct recordx *ptx) {
    printf("enter a name: ");
    scanf(" %[^\n]", ptx->name2);
}


int main() {


fucntionName(&ptx);
    return 0;
}