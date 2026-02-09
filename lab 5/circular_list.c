#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *insert_end(Node *last, int data)
{
    if (last == NULL)
    {
        Node *new_node = create_node(data);
        last = new_node;
        last->next = last; // Points to itself
        return last;
    }

    Node *new_node = create_node(data);
    new_node->next = last->next; // Point to the head
    last->next = new_node;
    last = new_node;
    return last;
}

void display(Node *last)
{
    if (last == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    Node *head = last->next;
    printf("Circular List: ");
    do
    {
        printf("%d -> ", head->data);
        head = head->next;
    } while (head != last->next);
    printf("(HEAD)\n");
}

int get_length(Node *last)
{
    if (last == NULL)
        return 0;
    Node *head = last->next;
    int count = 0;
    do
    {
        count++;
        head = head->next;
    } while (head != last->next);
    return count;
}

void split_list(Node *last, Node **head1_ref, Node **head2_ref)
{
    if (last == NULL || last->next == last)
    {
        printf("List too small to split.\n");
        return;
    }

    Node *head = last->next;
    Node *slow = head;
    Node *fast = head;

    // Floyd's Cycle
    while (fast->next != head && fast->next->next != head)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    *head1_ref = head;       // Head of first half
    *head2_ref = slow->next; // Head of second half

    // Make first half circular
    slow->next = *head1_ref;

    // Make second half circular
    Node *curr = *head2_ref;
    while (curr->next != head)
    {
        curr = curr->next;
    }
    curr->next = *head2_ref;

    printf("List Split Successfully.\n");
}

int is_sorted(Node *last)
{
    if (last == NULL)
        return 1;

    Node *head = last->next;
    Node *curr = head;
    int drop_count = 0;

    do
    {
        if (curr->data > curr->next->data)
        {
            drop_count++;
        }
        curr = curr->next;
    } while (curr != last);

    // Check the wrap-around (last to head)
    if (last->data > head->data)
    {
        drop_count++;
    }

    // A sorted circular list has exactly 1 drop (where Max connects to Min element) or 0 drops (all elements equal)
    return (drop_count <= 1);
}

Node *insert_sorted(Node *last, int data)
{
    Node *new_node = create_node(data);

    if (last == NULL)
    {
        last = new_node;
        last->next = last;
        return last;
    }

    Node *head = last->next;
    Node *curr = head;
    Node *prev = NULL;

    // If data is smaller than head or larger than tail, it goes at the beginning/end
    if (data < head->data || data >= last->data)
    {
        new_node->next = head;
        last->next = new_node;
        // If data is larger than last, the new node becomes the new last
        if (data >= last->data)
        {
            last = new_node;
        }
        return last;
    }

    // If it goes in the middle
    while (curr != last && curr->data < data)
    {
        prev = curr;
        curr = curr->next;
    }

    new_node->next = curr;
    prev->next = new_node;

    return last;
}

Node *reverse_list(Node *last)
{
    if (last == NULL || last->next == last)
        return last;

    Node *prev = last;
    Node *curr = last->next;
    Node *next_node;
    Node *head = last->next;

    // Iterate until curr loops back to head
    do
    {
        next_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_node;
    } while (curr != head);

    head->next = prev;

    return head;
}

Node *delete_kth_node(Node *last, int k)
{
    if (last == NULL)
        return NULL;
    if (k < 1)
        return last;

    Node *head = last->next;
    Node *curr = head;
    Node *prev = last;

    // If k=1, delete head
    if (k == 1)
    {
        if (last == head)
        { // Only 1 node
            free(head);
            return NULL;
        }
        last->next = head->next;
        free(head);
        return last;
    }

    // Traverse to k-th node
    for (int i = 1; i < k; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    if (curr == last)
        last = prev;

    free(curr);

    return last;
}

void display_linear_from_last(Node *last)
{

    if (!last)
        return;
    Node *head = last->next;
    last->next = NULL; // Break

    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void find_last_remaining(Node *last, int k)
{
    if (last == NULL)
        return;

    Node *curr = last->next; // Start at head
    Node *prev = last;

    int len = get_length(last);
    printf("Starting (k=%d) with %d nodes...\n", k, len);

    // Loop until only one node remains (it points to itself)
    while (curr->next != curr)
    {
        // Skip k-1 nodes
        for (int i = 1; i < k; i++)
        {
            prev = curr;
            curr = curr->next;
        }

        // Delete the k-th node
        printf("Deleting %d\n", curr->data);
        prev->next = curr->next;
        free(curr);

        // Move to next person
        curr = prev->next;
    }

    printf("The last remaining node is: %d\n", curr->data);
    free(curr);
}

Node *merge_cll(Node *last1, Node *last2)
{
    if (last1 == NULL)
        return last2;
    if (last2 == NULL)
        return last1;

    Node *head1 = last1->next;
    Node *head2 = last2->next;

    last1->next = head2;
    last2->next = head1;

    return last2;
}

void detect_and_count_loop(Node *last)
{
    if (last == NULL)
        return;

    Node *head = last->next;
    Node *slow = head;
    Node *fast = head;
    int loop_detected = 0;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            loop_detected = 1;
            break;
        }
    }

    if (loop_detected)
    {
        printf("Loop Detected.\n");
        // Count nodes
        int count = 1;
        Node *temp = slow;
        while (temp->next != slow)
        {
            count++;
            temp = temp->next;
        }
        printf("Number of nodes in the loop: %d\n", count);
    }
    else
    {
        printf("No Loop Detected (List is linear).\n");
    }
}

int main()
{
    Node *last = NULL;
    int choice, val, k;

    while (1)
    {
        printf("\nCircular Linked List Operations\n");
        printf("1. Insert Element at End\n");
        printf("2. Display List\n");
        printf("3. Split into two halves\n");
        printf("4. Check if Sorted\n");
        printf("5. Insert into Sorted List\n");
        printf("6. Reverse List\n");
        printf("7. Delete k-th Node\n");
        printf("8. Convert to Linear List\n");
        printf("9. Find Last Remaining\n");
        printf("10. Merge with another list\n");
        printf("11. Detect and Count Loop Nodes\n");
        printf("12. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &val);
            last = insert_end(last, val);
            break;
        case 2:
            display(last);
            break;
        case 3:
        {
            Node *head1 = NULL, *head2 = NULL;
            if (last == NULL)
            {
                printf("Empty.\n");
                break;
            }

            split_list(last, &head1, &head2);

            printf("Half 1: ");
            Node *curr = head1;
            if (curr)
            {
                do
                {
                    printf("%d ", curr->data);
                    curr = curr->next;
                } while (curr != head1);
            }
            printf("\nHalf 2: ");
            curr = head2;
            if (curr)
            {
                do
                {
                    printf("%d ", curr->data);
                    curr = curr->next;
                } while (curr != head2);
            }
        }
        break;
        case 4:
            if (is_sorted(last))
                printf("List IS sorted.\n");
            else
                printf("List is NOT sorted.\n");
            break;
        case 5:
            printf("Enter data to insert: ");
            scanf("%d", &val);
            last = insert_sorted(last, val);
            break;
        case 6:
            last = reverse_list(last);
            printf("List Reversed.\n");
            break;
        case 7:
            printf("Enter k: ");
            scanf("%d", &k);
            last = delete_kth_node(last, k);
            printf("Node deleted.\n");
            break;
        case 8:
            printf("Converting to linear and displaying:\n");
            display_linear_from_last(last);
            last = NULL;
            break;
        case 9:
            printf("Enter k (step size): ");
            scanf("%d", &k);
            find_last_remaining(last, k);
            last = NULL;
            break;
        case 10:
        {
            Node *l1 = NULL, *l2 = NULL;
            l1 = insert_end(l1, 10);
            l1 = insert_end(l1, 20);
            l2 = insert_end(l2, 30);
            l2 = insert_end(l2, 40);
            printf("List 1: ");
            display(l1);
            printf("List 2: ");
            display(l2);
            last = merge_cll(l1, l2);
            printf("Merged. New Main List:\n");
            display(last);
        }
        break;
        case 11:
            detect_and_count_loop(last);
            break;
        case 12:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}