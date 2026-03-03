#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *front = NULL;
Node *rear = NULL;

Node *createNode(int value)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

void enqueue(int value)
{
    Node *n = createNode(value);
    if (rear == NULL)
        front = rear = n;
    else
    {
        rear->next = n;
        rear = n;
    }
}

int dequeue(int *out)
{
    if (front == NULL)
        return 0;

    Node *tmp = front;
    *out = tmp->data;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(tmp);
    return 1;
}

int isEmpty()
{
    return front == NULL;
}

void display()
{
    Node *temp = front;
    if (!temp)
    {
        printf("Queue empty\n");
        return;
    }
    printf("Queue: ");
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void reverseUsingStack()
{
    if (isEmpty())
        return;

    int stack[1000];
    int top = -1;
    int value;

    while (dequeue(&value))
        stack[++top] = value;

    while (top >= 0)
        enqueue(stack[top--]);

    printf("Queue reversed using stack.\n");
}

void reverseRecursion()
{
    int value;
    if (!dequeue(&value))
        return;

    reverseRecursion();
    enqueue(value);
}

int countElements()
{
    int count = 0;
    Node *temp = front;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void findMaxMin()
{
    if (isEmpty())
    {
        printf("Queue empty\n");
        return;
    }

    Node *temp = front;
    int max = temp->data;
    int min = temp->data;

    while (temp)
    {
        if (temp->data > max)
            max = temp->data;
        if (temp->data < min)
            min = temp->data;
        temp = temp->next;
    }

    printf("Max = %d\n", max);
    printf("Min = %d\n", min);
}

int isPalindrome(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
            return 0;
        left++;
        right--;
    }
    return 1;
}

void freeQueue()
{
    int temp;
    while (dequeue(&temp))
        ;
}

int main()
{
    int choice, value;
    char str[100];

    do
    {
        printf("\n1.Enqueue\n");
        printf("2.Dequeue\n");
        printf("3.Display\n");
        printf("4.Reverse (Stack)\n");
        printf("5.Reverse (Recursion)\n");
        printf("6.Count Elements\n");
        printf("7.Find Max and Min\n");
        printf("8.Check Palindrome (Deque)\n");
        printf("9.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            enqueue(value);
            break;

        case 2:
            if (dequeue(&value))
                printf("Dequeued: %d\n", value);
            else
                printf("Queue empty\n");
            break;

        case 3:
            display();
            break;

        case 4:
            reverseUsingStack();
            break;

        case 5:
            reverseRecursion();
            printf("Queue reversed using recursion.\n");
            break;

        case 6:
            printf("Total elements: %d\n", countElements());
            break;

        case 7:
            findMaxMin();
            break;

        case 8:
            printf("Enter string: ");
            scanf("%s", str);
            if (isPalindrome(str))
                printf("Palindrome\n");
            else
                printf("Not Palindrome\n");
            break;

        case 9:
            freeQueue();
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice\n");
        }

    } while (choice != 9);

    return 0;
}