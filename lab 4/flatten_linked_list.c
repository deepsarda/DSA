#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    struct Node *bottom;
    int data;
} Node;

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->bottom = NULL;
    return new_node;
}

Node *merge_lists(Node *a, Node *b)
{
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    Node *result;
    if (a->data <= b->data)
    {
        result = a;
        result->bottom = merge_lists(a->bottom, b);
    }
    else
    {
        result = b;
        result->bottom = merge_lists(a, b->bottom);
    }

    return result;
}

Node *flatten_linked_list(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    head->next = flatten_linked_list(head->next);
    head = merge_lists(head, head->next);

    return head;
}

Node *display_flattened_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->bottom;
    }
    printf("NULL\n");
    return head;
}

Node *free_list(Node *head)
{
    if (head == NULL)
        return NULL;

    Node *current = head;

    while (current != NULL)
    {
        Node *next_bottom = current->bottom;
        current->bottom = NULL;
        current = next_bottom;
    }

    current = head;
    while (current != NULL)
    {
        Node *next_node = current->next;
        current->next = NULL;
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
        printf("1. Add vertical element (bottom pointer).\n");
        printf("2. Add horizontal element (next pointer).\n");
        printf("3. Flatten the linked list.\n");
        printf("4. Display flattened list.\n");
        printf("5. Exit.\n");
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
            if (head == NULL)
            {
                head = new_node;
            }
            else
            {
                Node *current = head;
                while (current->bottom != NULL)
                {
                    current = current->bottom;
                }
                current->bottom = new_node;
            }
            break;
        }

        case 2:
        {
            int data;
            printf("Enter data (integer): ");
            scanf("%d", &data);
            Node *new_node = create_node(data);
            if (head == NULL)
            {
                head = new_node;
            }
            else
            {
                Node *current = head;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = new_node;
            }
            break;
        }

        case 3:
            head = flatten_linked_list(head);
            printf("Flattened the linked list.\n");
            break;

        case 4:
            display_flattened_list(head);
            break;

        case 5:
            head = free_list(head);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
