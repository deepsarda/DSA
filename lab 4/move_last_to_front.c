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
    new_node->next = NULL;
    return new_node;
}

Node *move_last_to_front(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    Node *current = head;
    Node *second_last = NULL;

    // Find the last and second last node
    while (current->next != NULL)
    {
        second_last = current;
        current = current->next;
    }

    second_last->next = NULL;
    current->next = head;
    head = current;

    return head;
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

Node *free_list(Node *head)
{
    Node *current = head;
    Node *next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    return NULL;
}

int main()
{
    Node *head = NULL;

    while (1)
    {
        printf("1. Add element at head.\n");
        printf("2. Move last node to front.\n");
        printf("3. Display list.\n");
        printf("4. Exit.\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int data;
            printf("Enter data (integer): ");
            scanf("%d", &data);
            Node *new_node = create_node(data);
            new_node->next = head;
            head = new_node;
            break;
        }

        case 2:
            head = move_last_to_front(head);
            if (head != NULL)
            {
                printf("Moved last node to front.\n");
            }
            else
            {
                printf("The list is empty.\n");
            }
            break;

        case 3:
            display_list(head);
            break;

        case 4:
            head = free_list(head);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
