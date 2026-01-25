#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int data;
} Node;

Node *detect_and_remove_cycle(Node *head)
{
    if (head == NULL)
        return head;

    Node *slow = head;
    Node *fast = head;

    int cycle_found = 0;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            cycle_found = 1;
            break;
        }
    }

    if (cycle_found)
    {
        slow = head;
        Node *prev = NULL;

        // Find the start of the cycle
        while (slow != fast)
        {
            prev = fast;
            slow = slow->next;
            fast = fast->next;
        }

        // Remove the cycle
        prev->next = NULL;
    }

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

    // Creating a list with a cycle : 1 -> 2 -> 3 -> 4 -> 5
    Node *head = (Node *)malloc(sizeof(Node));
    Node *second = (Node *)malloc(sizeof(Node));
    Node *third = (Node *)malloc(sizeof(Node));
    Node *fourth = (Node *)malloc(sizeof(Node));
    Node *fifth = (Node *)malloc(sizeof(Node));
    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = fourth;

    fourth->data = 4;
    fourth->next = fifth;

    fifth->data = 5;

    fifth->next = third; // Creates a cycle

    printf("List before removing cycle:\n");

    head = detect_and_remove_cycle(head);

    printf("List after removing cycle:\n");
    display_list(head);

    Node *current = head;
    Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}