#include <stdio.h>

int main() {
    char name[50];
    int total = 0, ans1, ans2, ans3, ans4, ans5;
    float ave = 0.0;

    printf("Enter student name: ");
    scanf("%s", name);

    printf("Enter answer for Question 1: ");
    scanf("%d", &ans1);

    printf("Enter answer for Question 2: ");
    scanf("%d", &ans2);

    printf("Enter answer for Question 3: ");
    scanf("%d", &ans3);

    printf("Enter answer for Question 4: ");
    scanf("%d", &ans4);

    printf("Enter answer for Question 5: ");
    scanf("%d", &ans5);

    // Question 1
    if (ans1 == 1)
        total += 1;
    else {
    if (ans1 == 2)
        total += 2;
    else {
    if (ans1 == 3)
        total += 3;
    else {
    if (ans1 == 4)
        total += 4;
    else {
    if (ans1 == 5)
        total += 5;
    else {printf("\nQuestion #1: Out of range");}
                }
            }
        }
    }

    // Question 2
    if (ans2 == 1)
        total += 1;
    else {
    if (ans2 == 2)
        total += 2;
    else {
    if (ans2 == 3)
        total += 3;
    else {
    if (ans2 == 4)
        total += 4;
    else {
    if (ans2 == 5)
        total += 5;
    else {printf("\nQuestion #2: Out of range");}
                }
            }
        }
    }

    // Question 3
    if (ans3 == 1)
        total += 1;
    else {
    if (ans3 == 2)
        total += 2;
    else {
    if (ans3 == 3)
        total += 3;
    else {
    if (ans3 == 4)
        total += 4;
    else {
    if (ans3 == 5)
        total += 5;
    else {printf("\nQuestion #3: Out of range");}
                }
            }
        }
    }

    // Question 4
    if (ans4 == 1)
        total += 1;
    else {
    if (ans4 == 2)
        total += 2;
    else {
    if (ans4 == 3)
        total += 3;
    else {
    if (ans4 == 4)
        total += 4;
    else {
    if (ans4 == 5)
        total += 5;
    else {printf("\nQuestion #4: Out of range");}
                }
            }
        }
    }

    // Question 5
    if (ans5 == 1)
        total += 1;
    else {
    if (ans5 == 2)
        total += 2;
    else {
    if (ans5 == 3)
        total += 3;
    else {
    if (ans5 == 4)
        total += 4;
    else {
    if (ans5 == 5)
        total += 5;
    else {printf("\nQuestion #5: Out of range");}
                }
            }
        }
    }
    //process
    ave = total / 5.0;

    printf("\n%s, your total score is %d, and your average score is %.1f", name, total, ave);

    return 0;
}