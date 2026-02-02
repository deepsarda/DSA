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

Node *reverse_list(Node *head)
{
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

int check_palindrome(Node *head)
{
    if (head == NULL || head->next == NULL)
        return 1; // Empty or single node is palindrome

    Node *slow = head;
    Node *fast = head;

    // Find the middle of the linked list
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Reverse the second half
    Node *second_half = reverse_list(slow);
    Node *second_half_head = second_half; // Keep reference to restore later

    // Compare the two halves
    Node *first = head;
    int is_palindrome = 1;

    while (second_half != NULL)
    {
        if (first->data != second_half->data)
        {
            is_palindrome = 0;
            break;
        }
        first = first->next;
        second_half = second_half->next;
    }

    // Restore the second half by reversing it back
    reverse_list(second_half_head);

    return is_palindrome;
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
        printf("2. Check if it is a palindrome.\n");
        printf("3. Display list.\n");
        printf("4. Exit.\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            int data;
            printf("Enter data (integer): ");
            scanf("%d", &data);
            Node *new_node = create_node(data);
            new_node->next = head;
            head = new_node;
            break;

        case 2:
            int result = check_palindrome(head);
            if (result)
                printf("The linked list is a palindrome.\n");
            else
                printf("The linked list is not a palindrome.\n");
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
}