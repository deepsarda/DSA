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

Node *free_list(Node *head)
{
    Node *current = head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    return NULL;
}

int main()
{
    Node *head = NULL;
    Node *orignal_head = NULL;
    while (1)
    {
        int choice;
        printf("1. Insert at head\n");
        printf("2. Undo\n");
        printf("3. Print List\n");
        printf("4. exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int *data = (int *)malloc(sizeof(int));
            printf("Enter data (integer): ");
            scanf("%d", data);
            head = insert_at_head(head, data);

            if (orignal_head == NULL)
                orignal_head = head;
        }
        else if (choice == 2)
        {
            if (head != NULL && head != orignal_head)
            {
                Node *temp = head;
                head = head->next;
                free(temp->data);
                free(temp);
            }
            else
            {
                printf("No more undos available!\n");
            }
        }
        else if (choice == 3)
        {
            Node *current = head;
            printf("Current List: ");
            while (current != NULL)
            {
                printf("%d -> ", *(int *)(current->data));
                current = current->next;
            }
            printf("NULL\n");
        }
        else if (choice == 4)
        {
            head = free_list(head);
            printf("List freed. Exiting.\n");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}