#include <stdio.h>
//proper divisor
// interger N
//



void divisor(int N,int sumpro) {

    if(sumpro < N ) {
        printf("%d < %d is Deficient",sumpro, N);
    }
    
    if(sumpro == N ) {
        printf("%d = %d is Perfect",sumpro, N);
    }
    
    if(sumpro > N ) {
        printf("%d > %d is Abundant",sumpro, N);
    }
}



int main() {
    int N, sumpro = 0;
    
    printf("Enter a Number: ");
    scanf("%d", &N);
    printf("inputed number is: %d", N);
    printf("\nProper divisors are: ");

    for (int i = 1; i < N; i++) {
        if(N % i == 0) {
            sumpro += i;
            printf("%d ", i);
        }
    }
    printf("\nSum of proper divisor: %d \n", sumpro);

    divisor(N, sumpro);

    return 0;
}