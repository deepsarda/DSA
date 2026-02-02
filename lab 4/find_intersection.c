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

Node *find_intersection(Node *headA, Node *headB)
{
    Node *ptrA = headA;
    Node *ptrB = headB;

    while (ptrA != ptrB)
    {
        ptrA = (ptrA == NULL) ? headB : ptrA->next;
        ptrB = (ptrB == NULL) ? headA : ptrB->next;
    }

    return ptrA;
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
    Node *common1 = create_node(30);
    Node *common2 = create_node(40);
    Node *common3 = create_node(50);

    common1->next = common2;
    common2->next = common3;

    Node *headA = create_node(10);
    Node *temp = create_node(20);
    headA->next = temp;
    temp->next = common1;

    Node *headB = create_node(100);
    Node *temp2 = create_node(200);
    headB->next = temp2;
    temp2->next = common1;

    printf("List A: ");
    display_list(headA);
    printf("List B: ");
    display_list(headB);

    Node *intersection = find_intersection(headA, headB);
    if (intersection != NULL)
        printf("Intersection found at data: %d\n", intersection->data);
    else
        printf("No intersection found.\n");

    free(headA->next);
    free(headA);
    free(headB->next);
    free(headB);

    return 0;
}