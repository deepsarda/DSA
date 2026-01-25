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

Node *delete_nth_last_node(Node *head, int n)
{
    Node *fast = head;
    Node *slow = head;
    Node *previous = NULL;

    for (int i = 0; i < n; i++)
    {
        if (fast == NULL)
        {

            return head;
        }
        fast = fast->next;
    }

    if (fast == NULL)
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }

    while (fast != NULL)
    {
        previous = slow;
        slow = slow->next;
        fast = fast->next;
    }

    previous->next = slow->next;
    free(slow);

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

int main()
{
    Node *head = NULL;

    while (1)
    {
        int choice;
        printf("1. Insert at beginning\n");
        printf("2. Delete nth last node\n");
        printf("3. Display list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        int data;
        int n;

        if (choice == 1)
        {
            printf("Enter data (integer): ");
            scanf("%d", &data);
            Node *new_node = create_node(data);
            new_node->next = head;
            head = new_node;
        }
        else if (choice == 2)
        {
            printf("Enter n to delete the nth last node: ");
            scanf("%d", &n);
            head = delete_nth_last_node(head, n);
        }
        else if (choice == 3)
        {
            display_list(head);
        }
    }
}