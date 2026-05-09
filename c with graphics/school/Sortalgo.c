#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int arr[10];
    srand(time(NULL));
    for(int i = 0; i < 10; i++) {
        arr[i] = (rand() % 100) + 1;
        printf("%d ", arr[i]);
    }

    for(int o = 0; o < 10 ; o++){
        for(int h = 0; h < 10 - 1 - o; h++) {
            if(arr[h] > arr[h + 1]) {
                int temp = arr[h];
                arr[h] = arr[h + 1];
                arr[h + 1] = temp;
            }
        }
    }
    printf("\n");

     for(int a = 0; a < 10; a++) {
        printf("%d ", arr[a]);
     }
    return 0;
}