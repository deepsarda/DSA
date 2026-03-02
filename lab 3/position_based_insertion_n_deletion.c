#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    struct Node *next;
    void *data;
} Node;

Node *create_node(Node *next, void *data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = next;
    new_node->data = data;
    return new_node;
}

Node *insert_at_position(Node *head, void *data, int position)
{
    if (position == 0)
    {
        return create_node(head, data);
    }

    Node *current = head;
    int index = 0;

    while (current != NULL && index < position - 1)
    {
        current = current->next;
        index++;
    }

    if (current == NULL)
    {
        // Position is greater than the length of the list, insert at the end
        return head;
    }

    Node *new_node = create_node(current->next, data);
    current->next = new_node;

    return head;
}

Node *delete_at_position(Node *head, int position)
{
    if (head == NULL)
        return NULL;

    if (position == 0)
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }

    Node *current = head->next;
    Node *previous = head;
    int index = 1;

    while (current != NULL)
    {
        if (index == position)
        {
            previous->next = current->next;
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
        index++;
    }

    return head;
}

Node *display_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d -> ", *(int *)current->data);
        current = current->next;
    }
    printf("NULL\n");
    return head;
}

int main()
{
    Node *head = NULL;

    while (1)
    {
        int choice;
        printf("1. Insert at position\n");
        printf("2. Delete at position\n");
        printf("3. Display list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        int *data;
        int position;

        if (choice == 1)
        {
            data = (int *)malloc(sizeof(int));
            printf("Enter data (integer): ");
            scanf("%d", data);
            printf("Enter position to insert: ");
            scanf("%d", &position);
            head = insert_at_position(head, data, position);
        }
        else if (choice == 2)
        {
            printf("Enter position to delete: ");
            scanf("%d", &position);
            head = delete_at_position(head, position);
        }
        else if (choice == 3)
        {
            display_list(head);
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}