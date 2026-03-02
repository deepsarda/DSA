#include <stdio.h>
#include <stdlib.h>

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
    if (n == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

void enqueue(int value)
{
    Node *n = createNode(value);
    if (rear == NULL)
    {
        front = rear = n;
    }
    else
    {
        rear->next = n;
        rear = n;
    }
    printf("%d enqueued.\n", value);
}

int dequeue(int *out)
{
    if (front == NULL)
    {
        return 0;
    }
    Node *tmp = front;
    *out = tmp->data;
    front = front->next;
    if (front == NULL)
        rear = NULL;
    free(tmp);
    return 1;
}

int isEmpty(void)
{
    return front == NULL;
}

int frontElement(int *out)
{
    if (front == NULL)
        return 0;
    *out = front->data;
    return 1;
}

void freeQueue(void)
{
    Node *cur = front;
    while (cur)
    {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    front = rear = NULL;
}

int main(void)
{
    int choice;
    int value;
    int result;

    do
    {
        printf("\n--- Queue (Linked List) Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. isEmpty\n");
        printf("4. Front (peek)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter integer to enqueue: ");
            if (scanf("%d", &value) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
                printf("Invalid input. Aborting enqueue.\n");
            }
            else
            {
                enqueue(value);
            }
            break;

        case 2:
            if (dequeue(&value))
            {
                printf("Dequeued: %d\n", value);
            }
            else
            {
                printf("Queue is empty. Nothing to dequeue.\n");
            }
            break;

        case 3:
            printf(isEmpty() ? "Queue is empty.\n" : "Queue is NOT empty.\n");
            break;

        case 4:
            if (frontElement(&value))
            {
                printf("Front element: %d\n", value);
            }
            else
            {
                printf("Queue is empty. No front element.\n");
            }
            break;

        case 5:
            printf("Exiting and freeing memory...\n");
            freeQueue();
            break;

        default:
            printf("Invalid choice. Try 1..5.\n");
        }

    } while (choice != 5);

    return 0;
}