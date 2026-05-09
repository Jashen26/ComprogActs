#include <stdio.h>

// bodyweight index 


int main() {
    float weight, h, height;

    printf("enter your weight:(in pounds)\n");
    scanf("%f", &weight);

    printf("enter your height:(in inches)\n");
    scanf(" %f", &h);

    
    height = h * h;
    float result = 703 * weight / height;


    // printf("%.2f", result);
    if (result < 18.4){
        printf("you are underweight. EAT MORE.");
    }
    else if(result == 18.5 || result < 24.19) {
        printf("you are normal.");
    }
    else if(result == 25 || result < 29.9) {
        printf("you are overweight");
    }
    else {
        printf("you are obese");
    }
    return 0;
}