#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int data;
} Node;

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    return new_node;
}

Node *insert_at_tail(Node *tail, int data)
{
    Node *new_node = create_node(data);

    if (tail == NULL)
        return new_node;

    tail->next = new_node;

    return new_node;
}

Node *display_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    return head;
}

int main()
{

    Node *head = NULL;
    Node *tail = NULL;

    while (1)
    {

        printf("1. Insert node at end.");
        printf("2. Display list.");
        printf("3. Exit.");

        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int data;
            printf("Enter data (integer): ");
            scanf("%d", &data);

            if (head == NULL)
            {
                head = insert_at_tail(tail, data);
                tail = head;
            }
            else
            {
                tail = insert_at_tail(tail, data);
            }
        }
        else if (choice == 2)
        {
            display_list(head);
        }
        else if (choice == 3)
        {
            break;
        }
    }
}