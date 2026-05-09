#include <stdio.h>
#include <stdlib.h>

void KOMPUTE(int *PointA, int *Point_B, int n) {
    for (int i = 0; i < n - 1; i++) {
        Point_B[i] = PointA[i] + PointA[i + 1];
        printf("Point_B[%d] = PointA[%d] + PointA[%d] = %d + %d = %d\n",
               i, i, i + 1, PointA[i], PointA[i + 1], Point_B[i]);
    }
}

int main() {
    int n = 10;
    int *PointA  = (int *)malloc(n * sizeof(int));
    int *Point_B = (int *)malloc((n - 1) * sizeof(int));

    if (PointA == NULL || Point_B == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter 10 integers:\n");
    for (int i = 0; i < n; i++) {
        printf("PointA[%d]: ", i);
        scanf("%d", (PointA + i));
    }

    printf("\nKOMPUTE Results:\n");
    KOMPUTE(PointA, Point_B, n);

    printf("\nPointer PointA:\n");
    for (int i = 0; i < n; i++)
        printf("PointA[%d] = %d\n", i, *(PointA + i));

    printf("\nPointer Point_B:\n");
    for (int i = 0; i < n - 1; i++)
        printf("Point_B[%d] = %d\n", i, *(Point_B + i));

    free(PointA);
    free(Point_B);

    return 0;
}