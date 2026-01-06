#include <stdio.h>
#include <stdlib.h>

int main()
{

    int x, y;
    printf("Enter the dimension of the array: ");
    scanf("%d %d", &x, &y);

    printf("Enter values: ");
    int array[x][y];

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            scanf("%d", &array[i][j]);
        }
    }

    printf("The array is:\n");

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}