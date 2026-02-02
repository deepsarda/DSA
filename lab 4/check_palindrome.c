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

int check_palindrome(Node *head)
{
    Node *slow = head;
    Node *fast = head;
    Node *prev = NULL;
    Node *next = NULL;

    // Find the middle of the linked list
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }

    Node *second_half = NULL;
    if (fast != NULL) // Odd number of elements
    {
        second_half = slow->next;
    }
    else // Even number of elements
    {
        second_half = slow;
    }

    Node *first_half = prev;

    // Compare the two halves
    while (first_half != NULL && second_half != NULL)
    {
        if (first_half->data != second_half->data)
        {
            return 0; // Not a palindrome
        }
        first_half = first_half->next;
        second_half = second_half->next;
    }

    return 1; // Is a palindrome
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
    while (1)
    {
        printf("1. Add element at head.\n");
        printf("2. Check if it is a palindrome.\n");
        printf("3. Display list.\n");
        printf("4. Exit.\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        Node *head = NULL;

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

        case 3:
            display_list(head);
            break;

        case 4:
            head = free_list(head);
            return;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}