#include <stdio.h>
#include <stdlib.h>

int main()
{
    int quantity, *student, (*array)[3], subject = 3, sum = 0;

    printf("how many student are there: ");
    scanf("%d", &quantity);

    array = malloc(quantity * sizeof(*array));

    if (student == NULL)
        return 1;

    for (int i = 0; i < quantity; i++)
    {
        for (int j = 0; j < subject; j++)
        {
            printf("student[%d]grade for subject[%d]", i+1 ,j + 1);
            scanf("%d", &array[i][j]);
        }
    }

    for(int i = 0; i < quantity; i++) {
        printf("\nstudent[%d]\nhave an average of %d\n", i+1, (array[i][0]+array[i][1]+array[i][2])/3);
    }


    free(student);
    return 0;
}