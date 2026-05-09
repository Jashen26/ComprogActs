#include <stdio.h>

int main()
{
    char name[100];int sum, point, ave;int ans, ans2, ans3, ans4, ans5;printf("input a name:");scanf("%s", name);point = 0;printf("no.1 answer: ");scanf("%d", &ans);switch (ans){case 1:point++;break;case 2:point += 2;break;case 3:point += 3;break;case 4:point += 4;break;case 5:point += 5;break;default:point +=0;}printf("no.2 answer: ");scanf("%d", &ans2);switch (ans2){case 1:point++;break;case 2:point += 2;break;case 3:point += 3;break;case 4:point += 4;break;case 5:point += 5;break;default:point +=0;}printf("no.3 answer: ");scanf("%d", &ans3);switch (ans3){case 1:point++;break;case 2:point += 2;break;case 3:point += 3;break;case 4:point += 4;break;case 5:point += 5;break;default:point +=0;}printf("no.4 answer: ");scanf("%d", &ans4);switch (ans4){case 1:point++;break;case 2:point += 2;break;case 3:point += 3;break;case 4:point += 4;break;case 5:point += 5;break;default:point +=0;}printf("no.5 answer: ");scanf("%d", &ans5);switch (ans5){case 1:point++;break;case 2:point += 2;break;case 3:point += 3;break;case 4:point += 4;break;case 5:point += 5;break;default:point +=0;}printf("%s, scores %d with an average of %d ", name, point, point / 5);

    return 0;
} 