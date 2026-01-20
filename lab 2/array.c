#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int SubArray1[10];
    int SubArray2[10];
    int MainArray[20];
    int mainSize;
    int sub1Size;
    int sub2Size;
} Array;

void displayArray(int arr[], int size, const char *name)
{
    printf("%s: [", name);
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}

void displayMainArray(Array *array)
{
    displayArray(array->MainArray, array->mainSize, "MainArray");
}

void displaySubArray1(Array *array)
{
    displayArray(array->SubArray1, array->sub1Size, "SubArray1");
}

void displaySubArray2(Array *array)
{
    displayArray(array->SubArray2, array->sub2Size, "SubArray2");
}

void insertAtPosition(Array *array, int pos, int element)
{
    if (pos < 0 || pos > array->mainSize || array->mainSize >= 20)
    {
        printf("Invalid position or array is full!\n");
        return;
    }
    for (int i = array->mainSize; i > pos; i--)
    {
        array->MainArray[i] = array->MainArray[i - 1];
    }
    array->MainArray[pos] = element;
    array->mainSize++;
    printf("Element %d inserted at position %d.\n", element, pos);
    displayMainArray(array);
}

void deleteFromPosition(Array *array, int pos)
{
    if (pos < 0 || pos >= array->mainSize)
    {
        printf("Invalid position!\n");
        return;
    }
    printf("Element %d deleted from position %d.\n", array->MainArray[pos], pos);
    for (int i = pos; i < array->mainSize - 1; i++)
    {
        array->MainArray[i] = array->MainArray[i + 1];
    }
    array->mainSize--;
    displayMainArray(array);
}

void reverseWithTempArray(Array *array)
{
    int tempArray[20];
    for (int i = 0; i < array->mainSize; i++)
    {
        tempArray[i] = array->MainArray[array->mainSize - 1 - i];
    }
    for (int i = 0; i < array->mainSize; i++)
    {
        array->MainArray[i] = tempArray[i];
    }
    printf("Array reversed using temporary array.\n");
    displayMainArray(array);
}

void reverseInPlace(Array *array)
{
    int left = 0, right = array->mainSize - 1;
    while (left < right)
    {
        int temp = array->MainArray[left];
        array->MainArray[left] = array->MainArray[right];
        array->MainArray[right] = temp;
        left++;
        right--;
    }
    printf("Array reversed in-place.\n");
    displayMainArray(array);
}

void copyFromSubArray(Array *array, int whichSubArray)
{
    if (whichSubArray == 1)
    {
        if (array->mainSize + array->sub1Size > 20)
        {
            printf("Not enough space in MainArray!\n");
            return;
        }
        for (int i = 0; i < array->sub1Size; i++)
        {
            array->MainArray[array->mainSize++] = array->SubArray1[i];
        }
        printf("SubArray1 copied to MainArray.\n");
    }
    else if (whichSubArray == 2)
    {
        if (array->mainSize + array->sub2Size > 20)
        {
            printf("Not enough space in MainArray!\n");
            return;
        }
        for (int i = 0; i < array->sub2Size; i++)
        {
            array->MainArray[array->mainSize++] = array->SubArray2[i];
        }
        printf("SubArray2 copied to MainArray.\n");
    }
    else
    {
        printf("Invalid subarray number!\n");
        return;
    }
    displayMainArray(array);
}

void mergeSortedDescending(Array *array)
{
    int merged[20];
    int mergedSize = 0;
    int i = 0, j = 0;

    while (i < array->sub1Size && j < array->sub2Size)
    {
        if (array->SubArray1[i] >= array->SubArray2[j])
        {
            merged[mergedSize++] = array->SubArray1[i++];
        }
        else
        {
            merged[mergedSize++] = array->SubArray2[j++];
        }
    }

    while (i < array->sub1Size)
    {
        merged[mergedSize++] = array->SubArray1[i++];
    }

    while (j < array->sub2Size)
    {
        merged[mergedSize++] = array->SubArray2[j++];
    }

    printf("Merged sorted arrays in descending order: [");
    for (int k = 0; k < mergedSize; k++)
    {
        printf("%d", merged[k]);
        if (k < mergedSize - 1)
            printf(", ");
    }
    printf("]\n");
}

int sumWithoutRecursion(Array *array)
{
    int sum = 0;
    for (int i = 0; i < array->mainSize; i++)
    {
        sum += array->MainArray[i];
    }
    return sum;
}

int sumWithRecursion(Array *array, int index)
{
    if (index == array->mainSize)
        return 0;
    return array->MainArray[index] + sumWithRecursion(array, index + 1);
}

void searchElement(Array *array, int value)
{
    int found = -1;
    for (int i = 0; i < array->mainSize; i++)
    {
        if (array->MainArray[i] == value)
        {
            found = i;
            break;
        }
    }

    if (found != -1)
    {
        printf("Element %d found at position %d.\n", value, found);
    }
    else
    {
        printf("Element %d not found in MainArray.\n", value);
    }
}

void separateOddEven(Array *array)
{
    int odd[20], even[20];
    int oddSize = 0, evenSize = 0;

    for (int i = 0; i < array->mainSize; i++)
    {
        if (array->MainArray[i] % 2 == 0)
        {
            even[evenSize++] = array->MainArray[i];
        }
        else
        {
            odd[oddSize++] = array->MainArray[i];
        }
    }

    displayArray(odd, oddSize, "Odd numbers");
    displayArray(even, evenSize, "Even numbers");
}

void separatePositiveNegative(Array *array)
{
    int positive[20], negative[20];
    int posSize = 0, negSize = 0;

    for (int i = 0; i < array->mainSize; i++)
    {
        if (array->MainArray[i] >= 0)
        {
            positive[posSize++] = array->MainArray[i];
        }
        else
        {
            negative[negSize++] = array->MainArray[i];
        }
    }

    displayArray(positive, posSize, "Positive numbers");
    displayArray(negative, negSize, "Negative numbers");
}

void displayMenu()
{
    printf("\n------- ARRAY OPERATIONS MENU ----\n");
    printf("1. Insert element at the end\n");
    printf("2. Insert element at the beginning\n");
    printf("3. Insert element at a specific position\n");
    printf("4. Delete element from the end\n");
    printf("5. Delete element from the beginning\n");
    printf("6. Delete element from a specific position\n");
    printf("7. Reverse array using temporary array\n");
    printf("8. Reverse array in-place\n");
    printf("9. Copy from SubArray to MainArray\n");
    printf("10. Merge sorted arrays in descending order\n");
    printf("11. Calculate sum (without recursion)\n");
    printf("12. Calculate sum (with recursion)\n");
    printf("13. Search for an element\n");
    printf("14. Separate odd and even numbers\n");
    printf("15. Separate positive and negative numbers\n");
    printf("16. Display MainArray\n");
    printf("17. Display SubArray1\n");
    printf("18. Display SubArray2\n");
    printf("0. Exit\n");
    printf("-----------------------------------\n");
}

int main()
{
    Array array;
    array.mainSize = 0;
    array.sub1Size = 0;
    array.sub2Size = 0;

    int choice, element, pos, value, index, sub;

    printf("Enter initial elements for SubArray1 (max 10, press -1 to stop):\n");
    while (array.sub1Size < 10)
    {
        printf("SubArray1[%d]: ", array.sub1Size);
        scanf("%d", &element);
        if (element == -1)
            break;
        array.SubArray1[array.sub1Size++] = element;
    }

    printf("\nEnter initial elements for SubArray2 (max 10, press -1 to stop):\n");
    while (array.sub2Size < 10)
    {
        printf("SubArray2[%d]: ", array.sub2Size);
        scanf("%d", &element);
        if (element == -1)
            break;
        array.SubArray2[array.sub2Size++] = element;
    }

    printf("\nEnter initial elements for MainArray (max 20, press -1 to stop):\n");
    while (array.mainSize < 20)
    {
        printf("MainArray[%d]: ", array.mainSize);
        scanf("%d", &element);
        if (element == -1)
            break;
        array.MainArray[array.mainSize++] = element;
    }

    while (1)
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to insert: ");
            scanf("%d", &element);
            insertAtPosition(&array, element, array.mainSize);
            break;

        case 2:
            printf("Enter element to insert: ");
            scanf("%d", &element);
            insertAtPosition(&array, element, 0);
            break;

        case 3:
            printf("Enter position (0-%d): ", array.mainSize);
            scanf("%d", &pos);
            printf("Enter element to insert: ");
            scanf("%d", &element);
            insertAtPosition(&array, pos, element);
            break;

        case 4:
            deleteFromPosition(&array, array.mainSize - 1);
            break;

        case 5:
            deleteFromPosition(&array, 0);
            break;

        case 6:
            printf("Enter position to delete (0-%d): ", array.mainSize - 1);
            scanf("%d", &pos);
            deleteFromPosition(&array, pos);
            break;

        case 7:
            reverseWithTempArray(&array);
            break;

        case 8:
            reverseInPlace(&array);
            break;

        case 9:
            printf("Choose subarray (1 or 2): ");
            scanf("%d", &sub);
            copyFromSubArray(&array, sub);
            break;

        case 10:
            mergeSortedDescending(&array);
            break;

        case 11:
            printf("Sum (without recursion): %d\n", sumWithoutRecursion(&array));
            break;

        case 12:
            printf("Sum (with recursion): %d\n", sumWithRecursion(&array, 0));
            break;

        case 13:
            printf("Enter value to search: ");
            scanf("%d", &value);
            searchElement(&array, value);
            break;

        case 14:
            separateOddEven(&array);
            break;

        case 15:
            separatePositiveNegative(&array);
            break;

        case 16:
            displayMainArray(&array);
            break;

        case 17:
            displaySubArray1(&array);
            break;

        case 18:
            displaySubArray2(&array);
            break;

        case 0:
            printf("Exiting program...\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}