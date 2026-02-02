#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    struct Node *random;
    int data;
} Node;

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->random = NULL;
    return new_node;
}

Node *clone_linked_list(Node *head)
{
    if (head == NULL)
        return NULL;

    // Insert cloned nodes after each original node
    Node *current = head;
    while (current != NULL)
    {
        Node *cloned = create_node(current->data);
        cloned->next = current->next;
        current->next = cloned;
        current = cloned->next;
    }

    // Set random pointers for cloned nodes
    current = head;
    while (current != NULL)
    {
        if (current->random != NULL)
        {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    // Separate the original and cloned lists
    current = head;
    Node *cloned_head = head->next;
    Node *cloned_current = cloned_head;

    while (current != NULL)
    {
        current->next = current->next->next;
        if (cloned_current->next != NULL)
        {
            cloned_current->next = cloned_current->next->next;
        }
        current = current->next;
        cloned_current = cloned_current->next;
    }

    return cloned_head;
}

Node *display_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        int random_data = (current->random != NULL) ? current->random->data : -1;
        printf("Data: %d, Random: %d -> ", current->data, random_data);
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
    Node *original_head = NULL;
    Node *cloned = NULL;

    while (1)
    {
        printf("1. Add element at head (original list).\n");
        printf("2. Set random pointer for element.\n");
        printf("3. Clone the linked list.\n");
        printf("4. Display original list.\n");
        printf("5. Display cloned list.\n");
        printf("6. Exit.\n");
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
            if (original_head == NULL)
            {
                original_head = head;
            }
            break;
        }

        case 2:
        {
            if (head == NULL)
            {
                printf("List is empty. Add elements first.\n");
                break;
            }
            int node_data, random_data;
            printf("Enter data of node: ");
            scanf("%d", &node_data);
            printf("Enter data to point to (random): ");
            scanf("%d", &random_data);

            Node *current = head;
            Node *target = NULL;

            // Find node with node_data
            while (current != NULL && current->data != node_data)
            {
                current = current->next;
            }

            // Find node with random_data
            Node *search = head;
            while (search != NULL && search->data != random_data)
            {
                search = search->next;
            }

            if (current != NULL && search != NULL)
            {
                current->random = search;
                printf("Random pointer set.\n");
            }
            else
            {
                printf("Invalid node data.\n");
            }
            break;
        }

        case 3:
        {
            cloned = clone_linked_list(head);
            printf("List cloned successfully.\n");
            break;
        }

        case 4:
            display_list(head);
            break;

        case 5:
        {
            display_list(cloned);
            break;
        }

        case 6:
            head = free_list(head);
            original_head = free_list(original_head);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
