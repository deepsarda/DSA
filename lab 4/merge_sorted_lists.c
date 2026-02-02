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

Node *merge_sorted_lists(Node *heads[], int k)
{
    if (k == 0 || heads[0] == NULL)
        return NULL;

    Node *head = heads[0];
    Node *sorted = head;
    Node **current = (Node **)malloc(k * sizeof(Node *));
    for (int i = 0; i < k; i++)
    {
        current[i] = heads[i];
    }

    current[0] = current[0]->next;

    while (1)
    {
        int found_non_empty = 0;
        int i;
        Node *min = NULL;
        int min_index = -1;

        // Find the first non-empty list
        for (i = 0; i < k; i++)
        {
            if (current[i] != NULL)
            {
                found_non_empty = 1;
                min = current[i];
                min_index = i;
                break;
            }
        }

        if (!found_non_empty)
        {
            free(current);
            return head;
        }

        // Find the minimum among remaining
        for (; i < k; i++)
        {
            if (current[i] != NULL && current[i]->data < min->data)
            {
                min = current[i];
                min_index = i;
            }
        }

        sorted->next = min;
        sorted = sorted->next;

        current[min_index] = min->next;
    }

    free(current);
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
    Node *heads[10];
    int k, i;
    printf("Enter number of lists to merge (max 10): ");
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        heads[i] = NULL;
        int n, j;
        printf("Enter number of elements in list %d: ", i + 1);
        scanf("%d", &n);
        Node *tail = NULL;
        for (j = 0; j < n; j++)
        {
            int data;
            printf("Enter element %d: ", j + 1);
            scanf("%d", &data);
            Node *new_node = create_node(data);
            if (heads[i] == NULL)
            {
                heads[i] = new_node;
                tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }

    Node *merged_head = merge_sorted_lists(heads, k);
    printf("Merged sorted list:\n");
    display_list(merged_head);

    merged_head = free_list(merged_head);

    return 0;
}