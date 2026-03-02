#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int priority;
    struct Node *nextPriority;
} Node;

Node *createNode(int p)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->priority = p;
    newNode->nextPriority = NULL;
    return newNode;
}

Node *push(Node *head, int p)
{
    Node *newNode = createNode(p);

    if (head == NULL || p < head->priority)
    {
        newNode->nextPriority = head;
        head = newNode;
        printf("Inserted priority %d\n", p);
        return head;
    }

    Node *temp = head;

    while (temp->nextPriority != NULL &&
           temp->nextPriority->priority < p)
    {
        temp = temp->nextPriority;
    }

    if (temp->priority == p ||
        (temp->nextPriority != NULL &&
         temp->nextPriority->priority == p))
    {
        printf("Priority already exists.\n");
        free(newNode);
        return head;
    }

    newNode->nextPriority = temp->nextPriority;
    temp->nextPriority = newNode;

    printf("Inserted priority %d\n", p);

    return head;
}

Node *pop(Node *head)
{
    if (head == NULL)
    {
        printf("Queue empty.\n");
        return head;
    }

    Node *temp = head;
    printf("Popped priority %d\n", temp->priority);
    head = head->nextPriority;
    free(temp);

    return head;
}

void peek(Node *head)
{
    if (head == NULL)
        printf("Queue empty.\n");
    else
        printf("Top priority: %d\n", head->priority);
}

void isEmpty(Node *head)
{
    if (head == NULL)
        printf("Queue is empty.\n");
    else
        printf("Queue is not empty.\n");
}

void display(Node *head)
{
    if (head == NULL)
    {
        printf("Queue empty.\n");
        return;
    }

    Node *temp = head;
    printf("Queue: ");
    while (temp != NULL)
    {
        printf("%d ", temp->priority);
        temp = temp->nextPriority;
    }
    printf("\n");
}

void freeQueue(Node *head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->nextPriority;
        free(temp);
    }
}

int main()
{
    int choice, p;
    Node *head = NULL;
    do
    {
        printf("\n1.Push\n");
        printf("2.Pop\n");
        printf("3.Peek\n");
        printf("4.isEmpty\n");
        printf("5.Display\n");
        printf("6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter priority (0 = highest): ");
            scanf("%d", &p);
            head = push(head, p);
            break;
        case 2:
            head = pop(head);
            break;
        case 3:
            peek(head);
            break;
        case 4:
            isEmpty(head);
            break;
        case 5:
            display(head);
            break;
        case 6:
            freeQueue(head);
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}