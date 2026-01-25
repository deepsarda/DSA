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

Node *insert_at_head(Node *head, void *data)
{
    Node *new_head = create_node(head, data);
    return new_head;
}

Node *insert_at_tail(Node *head, void *data)
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

Node *delete_by_value(Node *head, void *data)
{
    if (head == NULL)
        return NULL;

    if (head->data == data)
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }

    Node *current = head->next;
    Node *previous = head;

    while (current != NULL)
    {
        if (current->data == data)
        {
            previous->next = current->next;
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
    }

    return head;
}

Node *delete_by_position(Node *head, int position)
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

Node *search(Node *head, void *data)
{
    Node *current = head;

    while (current != NULL)
    {
        if (current->data == data)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

Node *reverse(Node *head)
{
    Node *previous = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    return previous;
}

int detect_cycle(Node *head)
{

    if (head == NULL)
        return 0;

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return 1;
        }
    }

    return 0;
}

void display_list(Node *head, void (*print_data)(void *))
{
    Node *current = head;

    while (current != NULL)
    {
        print_data(current->data);
        current = current->next;
    }
}

void print_int(void *data)
{
    printf("%d -> ", *(int *)data);
}

void print_string(void *data)
{
    printf("%s -> ", (char *)data);
}

void print_float(void *data)
{
    printf("%.2f -> ", *(float *)data);
}

void print_double(void *data)
{
    printf("%.2lf -> ", *(double *)data);
}

void print_char(void *data)
{
    printf("%c -> ", *(char *)data);
}

void free_list(Node *head)
{
    Node *current = head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int main()
{

    Node *head = NULL;

    while (1)
    {
        int choice;
        printf("\n1. Insert at head");
        printf("\n2. Insert at tail");
        printf("\n3. Delete by value");
        printf("\n4. Delete by position");
        printf("\n5. Search");
        printf("\n6. Reverse");
        printf("\n7. Detect cycle");
        printf("\n8. Display list");
        printf("\n9. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 9)
        {
            break;
        }

        int *data = (int *)malloc(sizeof(int));

        if (choice != 8)
        {
            printf("Enter data (integer): ");
            scanf("%d", data);
        }

        switch (choice)
        {
        case 1:
            head = insert_at_head(head, data);
            break;
        case 2:
            head = insert_at_tail(head, data);
            break;
        case 3:
            head = delete_by_value(head, data);
            free(data);
            break;
        case 4:
        {
            int position;
            printf("Enter position to delete: ");
            scanf("%d", &position);
            head = delete_by_position(head, position);
            free(data);
            break;
        }
        case 5:
        {
            Node *found = search(head, data);
            if (found)
                printf("Data found: %d\n", *(int *)found->data);
            else
                printf("Data not found.\n");
            free(data);
            break;
        }
        case 6:
            head = reverse(head);
            free(data);
            break;
        case 7:
        {
            int has_cycle = detect_cycle(head);
            if (has_cycle)
                printf("Cycle detected in the list.\n");
            else
                printf("No cycle in the list.\n");
            free(data);
            break;
        }
        case 8:
            display_list(head, print_int);
            printf("NULL\n");
            free(data);
            break;
        default:
            printf("Invalid choice!\n");
            free(data);
            break;
        }
    }
    return 0;
}