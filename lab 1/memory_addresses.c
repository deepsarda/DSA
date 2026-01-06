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

    printf("Elements of the 2D array in column-major order:\n");
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    printf("\n-------------------------------------------------\n");

    long base_address = (long)array;

    printf("The base address is %ld.\n\n", base_address);

    printf("The EXPECTED address of the 2D array elements in row-major order:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%ld ", base_address + 4 * (3 * i + j));
        }
        printf("\n");
    }

    printf("The EXPECTED address of the 2D array elements in column-major order:\n");
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%ld ", base_address + 4 * (3 * i + j));
        }
        printf("\n");
    }

    printf("\n-------------------------------------------------\n");

    printf("The ACTUAL address of the 2D array elements in row-major order:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%ld ", &array[i][j]);
        }
        printf("\n");
    }

    printf("The ACTUAL address of the 2D array elements in column-major order:\n");
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%ld ", &array[i][j]);
        }
        printf("\n");
    }
}