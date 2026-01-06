#include <stdio.h>

int main()
{
    int array[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    printf("Elements of the 2D array in row-major order:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    printf("The address of the 2D array elements in row-major order:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%ld ", &array[i][j]);
        }
        printf("\n");
    }
}