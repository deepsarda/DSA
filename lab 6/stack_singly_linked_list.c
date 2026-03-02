#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

// Create a new node
Node *create_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Create a new stack
Stack *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Check if stack is empty
int isEmpty(Stack *s)
{
    return s->top == NULL;
}

// Push operation - insert node at the beginning (top)
void push(Stack *s, int data)
{
    Node *new_node = create_node(data);
    new_node->next = s->top;
    s->top = new_node;
    printf("Pushed %d onto stack\n", data);
}

// Pop operation - delete node from the beginning (top) and return the data
int pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack underflow! Cannot pop from empty stack.\n");
        return -1;
    }
    
    Node *temp = s->top;
    int data = temp->data;
    s->top = s->top->next;
    free(temp);
    printf("Popped %d from stack\n", data);
    return data;
}

// Peek operation - return top element without removing it
int peek(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty! No element to peek.\n");
        return -1;
    }
    printf("Top element: %d\n", s->top->data);
    return s->top->data;
}

// Display all elements in the stack
void display(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("Stack elements (top to bottom): ");
    Node *current = s->top;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Menu-driven main function
int main()
{
    Stack *s = create_stack();
    int choice, data;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Is Empty\n");
        printf("5. Display Stack\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data to push: ");
            scanf("%d", &data);
            push(s, data);
            break;

        case 2:
            data = pop(s);
            if (data != -1)
            {
                printf("Popped element: %d\n", data);
            }
            break;

        case 3:
            peek(s);
            break;

        case 4:
            if (isEmpty(s))
                printf("Stack is empty!\n");
            else
                printf("Stack is not empty!\n");
            break;

        case 5:
            display(s);
            break;

        case 6:
            printf("\nExiting program...\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}