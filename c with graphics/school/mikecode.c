#include <stdio.h>

int main(void)
{
    float weight, height, bmi;

    // Input
    printf("Enter weight in pounds (lb): ");
    scanf("%f", &weight);
    printf("Enter height in inches (in): ");
    scanf("%f", &height);

    // BMI formula
    bmi = (703 * weight) / (height * height);

    // Output the calculation process
    printf("\n--- CALCULATION PROCESS ---\n");
    printf("BMI = (703 * %.1f) / (%.1f * %.1f)\n", weight, height, height);
    printf("BMI = %.1f\n", bmi);

    // Determine status
    printf("\n--- RESULT ---\n");
    printf("Your BMI is %.1f\n", bmi);

    if (bmi < 18.5)
        printf("Status: Underweight\n");
    else if (bmi >= 18.5 && bmi <= 24.9)
        printf("Status: Normal\n");
    else if (bmi >= 25.0 && bmi <= 29.9)
        printf("Status: Overweight\n");
    else
        printf("Status: Obese\n");

    return 0;
}