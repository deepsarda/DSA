#include <stdio.h>

int find_larget(int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int find_smallest(int arr[], int size)
{
    int min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int find_average(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum / size;
}

// Return index if found, otherwise -1
int find_element(int arr[], int size, int element)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == element)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;
    printf("Enter number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements of the array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d/%d: ", i + 1, n);
        scanf("%d", arr + i);
    }

    printf("Entered array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    int to_find;
    printf("\nEnter element to find: ");
    scanf("%d", &to_find);

    printf("Maximum element: %d\n", find_larget(arr, n));
    printf("Minimum element: %d\n", find_larget(arr, n));
    printf("Average: %d\n", find_average(arr, n));

    int find_result = find_element(arr, n, to_find);
    if (find_result >= 0)
    {
        printf("The element was found at %d\n", find_result + 1);
    }
    else
    {
        printf("We were unable to find the element.\n");
    }
}