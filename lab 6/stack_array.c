#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int capacity;
    int size;
    char data[];
} Stack;

Stack *create_stack(int capacity)
{
    Stack *s = (Stack *)malloc(sizeof(Stack) + sizeof(char) * (capacity));

    s->capacity = capacity;
    s->size = 0;

    return s;
}

void push(Stack *s, char data)
{
    if (s->capacity == s->size)
    {
        printf("Stackn Overflow!!!");
        return;
    }

    s->data[s->size] = data;

    s->size++;
}

char pop(Stack *s)
{
    if (s->size == 0)
    {
        printf("Underflow!!!");
        return '\0';
    }

    s->size--;
    char data = s->data[s->size];

    return data;
}

char peek(Stack *s)
{
    if (s->size == 0)
    {
        printf("Stack is empty.");
        return 0;
    }

    return s->data[s->size - 1];
}

int isEmpty(Stack *s)
{
    return s->size == 0;
}

int isFull(Stack *s)
{
    return s->size == s->capacity;
}

char *reverse_string(char str[], int n)
{
    Stack *s = create_stack(n);

    for (int i = 0; i < n; i++)
    {
        push(s, str[i]);
    }

    char *rev = malloc(sizeof(char) * ((n + 1)));

    for (int i = 0; i < n; i++)
    {
        rev[i] = pop(s);
    }

    rev[n] = '\0';

    return rev;
}

int check_balanced_parentheses(char str[], int n)
{
    Stack *s = create_stack(n);

    for (int i = 0; i < n; i++)
    {
        char ch = str[i];

        if (ch == '(' || ch == '{' || ch == '[')
        {
            push(s, ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (isEmpty(s))
                return 0;

            char top = pop(s);

            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '['))
            {
                return 0;
            }
        }
    }

    return isEmpty(s);
}

int higherAssociativity(char op, char stack_top)
{
    if (op == '/' || op == '*')
    {
        return 1;
    }

    return 0;
}

char *convert_to_postfix_from_infix(char str[], int n)
{

    Stack *s = create_stack(n);
    char *postfix = (char *)malloc(sizeof(char) * n + 1);
    int postfix_write_index = 0;

    for (int i = 0; i < n; i++)
    {
        char ch = str[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {

            postfix[postfix_write_index] = ch;
            postfix_write_index++;
        }

        else if (ch == ')')
        {
            while (!isEmpty(s) && peek(s) != '(')
            {
                postfix[postfix_write_index] = pop(s);
                postfix_write_index++;
            }
        }
        else if (ch == '(')
        {
            push(s, ch);
        }
        else
        {
            // Pop operaters based on associativity
            while (!isEmpty(s) && peek(s) != '(' && higherAssociativity(ch, peek(s)))
            {
                postfix[postfix_write_index] = pop(s);
                postfix_write_index++;
            }

            push(s, ch);
        }
    }

    while (!isEmpty(s))
    {
        if (peek(s) == '(')
        {
            pop(s);
            continue;
        }

        postfix[postfix_write_index] = pop(s);
        postfix_write_index++;
    }

    postfix[postfix_write_index] = '\0';

    return postfix;
}

int main()
{
    int choice;
    char input[100];
    int length;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Reverse a String\n");
        printf("2. Check Balanced Parentheses\n");
        printf("3. Convert Infix to Postfix\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice)
        {
        case 1:
            printf("Enter a string to reverse: ");
            fgets(input, sizeof(input), stdin);
            // Remove newline if present
            length = 0;
            while (input[length] != '\0' && input[length] != '\n')
                length++;
            input[length] = '\0';

            char *reversed = reverse_string(input, length);
            printf("Original string: %s\n", input);
            printf("Reversed string: %s\n", reversed);
            free(reversed);
            break;

        case 2:
            printf("Enter an expression with parentheses to check: ");
            fgets(input, sizeof(input), stdin);
            // Remove newline if present
            length = 0;
            while (input[length] != '\0' && input[length] != '\n')
                length++;
            input[length] = '\0';

            if (check_balanced_parentheses(input, length))
                printf("Parentheses are BALANCED!\n");
            else
                printf("Parentheses are NOT BALANCED!\n");
            break;

        case 3:
            printf("Enter an infix expression (e.g., A+B*C, (A+B)*(C-D)): ");
            fgets(input, sizeof(input), stdin);
            // Remove newline if present
            length = 0;
            while (input[length] != '\0' && input[length] != '\n')
                length++;
            input[length] = '\0';

            char *postfix = convert_to_postfix_from_infix(input, length);
            printf("Infix expression: %s\n", input);
            printf("Postfix expression: %s\n", postfix);
            free(postfix);
            break;

        case 4:
            printf("\nExiting program...\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
