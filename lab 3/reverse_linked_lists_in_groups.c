#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    struct Node *next;
    int *data;
} Node;

Node *create_node(Node *next, int *data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = next;
    new_node->data = data;
    return new_node;
}

Node *reverse_in_groups(Node *head, int k)
{
    Node *current = head;
    Node *previous = NULL;
    Node *next = NULL;
    int count = 0;

    // Reverse first k nodes of the linked list
    while (current != NULL && count < k)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
        count++;
    }

    // next is now a pointer to (k+1)th node, so we do recursive call
    if (next != NULL)
    {
        head->next = reverse_in_groups(next, k);
    }

    return previous;
}

Node *insert_at_tail(Node *head, int *data)
{
    Node *new_node = create_node(NULL, data);

    if (head == NULL)
        return new_node;

    Node *current = head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_node;

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
        printf("1. Insert at tail\n");
        printf("2. Reverse in groups\n");
        printf("3. Display list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        if (choice == 1)
        {
            int *data = (int *)malloc(sizeof(int));
            printf("Enter data (integer): ");
            scanf("%d", data);
            head = insert_at_tail(head, data);
        }
        else if (choice == 2)
        {
            int k;
            printf("Enter group size k: ");
            scanf("%d", &k);
            head = reverse_in_groups(head, k);
        }
        else if (choice == 3)
        {
            display_list(head);
        }
    }

    return 0;
}