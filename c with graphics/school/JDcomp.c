#include <stdio.h>

int main() {
    
    int hours = 0, cat = 0, bucket = 0;

    while(bucket < 2452) {
        hours++;

        if (hours % 3 == 0) {
            bucket += 162;
            bucket -= 28;
            cat += 28;

            printf("hours: %d, Drops in the bucket: %d - 28 = %d \n", hours, bucket + 28, bucket);
        }

        else {
            bucket += 162;
            printf("hours: %d, Drops in the bucket: %d\n", hours, bucket);
        }
    }

    if(bucket >= 2452) {
        printf("hours it takes to fill up the bucket: %d, drops drunked by the cat: %d", hours, cat);
    }


    return 0;
}