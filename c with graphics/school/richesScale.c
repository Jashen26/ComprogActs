#include <stdio.h>

int main() {
    double N;

    printf("enter the type of damage that can occur: ");
    scanf("%lf", &N);

if (N < 5.0) {
    printf("Little to now damage");

}
else if(N == 5.0 || N < 5.4) {
    printf("There are some damage");
}
else if(N == 5.5 || N < 6.4) {
    printf("There are serious damage");
}
else if(N == 6.5 || N < 7.4) {
    printf("Disaster! houses and buildings");
}
else {
    printf("CATASTROPE!!!!!");
}

    return 0;
}