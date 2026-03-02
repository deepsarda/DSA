#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node *enQueue(Node *rear, int value)
{
    Node *newNode = createNode(value);

    if (rear == NULL)
    {
        rear = newNode;
        rear->next = rear;
    }
    else
    {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d inserted into queue\n", value);

    return rear;
}

Node *deQueue(Node *rear)
{
    if (rear == NULL)
    {
        printf("Queue is empty\n");
        return rear;
    }

    Node *front = rear->next;

    if (rear == front)
    {
        printf("Deleted %d\n", front->data);
        free(front);
        rear = NULL;
    }
    else
    {
        printf("Deleted %d\n", front->data);
        rear->next = front->next;
        free(front);
    }

    return rear;
}

void front(Node *rear)
{
    if (rear == NULL)
        printf("Queue is empty\n");
    else
        printf("Front: %d\n", rear->next->data);
}

void get_rear(Node *rear)
{
    if (rear == NULL)
        printf("Queue is empty\n");
    else
        printf("Rear: %d\n", rear->data);
}

void display(Node *rear)
{
    if (rear == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    Node *temp = rear->next; // start from front
    printf("Queue: ");

    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != rear->next);

    printf("\n");
}

void freeQueue(Node *rear)
{
    if (rear == NULL)
        return;

    Node *front = rear->next;
    Node *temp;

    while (front != rear)
    {
        temp = front;
        front = front->next;
        free(temp);
    }

    free(rear);
    rear = NULL;
}

int main()
{
    int choice, value;
    Node *rear = NULL;
    do
    {
        printf("\n1. enQueue\n");
        printf("2. deQueue\n");
        printf("3. Front\n");
        printf("4. Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            rear = enQueue(rear, value);
            break;
        case 2:
            rear = deQueue(rear);
            break;
        case 3:
            front(rear);
            break;
        case 4:
            get_rear(rear);
            break;
        case 5:
            display(rear);
            break;
        case 6:
            freeQueue(rear);
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
        }

    } while (choice != 6);

    return 0;
}