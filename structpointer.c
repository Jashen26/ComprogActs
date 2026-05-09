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




int main() {

    return 0;
}