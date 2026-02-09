#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct DNode
{
    struct DNode *prev;
    struct DNode *next;
    struct DNode *random;
    int data;
} DNode;

int get_length(DNode *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

DNode *create_dnode(int data)
{
    DNode *new_node = (DNode *)malloc(sizeof(DNode));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->random = NULL;
    return new_node;
}

DNode *insert_end(DNode *head, int data)
{
    DNode *new_node = create_dnode(data);
    if (head == NULL)
        return new_node;

    DNode *current = head;
    while (current->next != NULL)
        current = current->next;

    current->next = new_node;
    new_node->prev = current;
    return head;
}

void display_dlist(DNode *head)
{
    DNode *current = head;
    printf("List: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        if (current->random)
            printf("(R:%d) ", current->random->data);

        if (current->next != NULL)
            printf("<-> ");
        current = current->next;
    }
    printf("\n");
}

DNode *free_dlist(DNode *head)
{
    DNode *current = head;
    DNode *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    return NULL;
}

DNode *reverse_dlist(DNode *head)
{
    DNode *current = head;
    DNode *temp = NULL;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL)
    {
        head = temp->prev;
    }
    return head;
}

void find_two_sum(DNode *head, int sum)
{
    if (head == NULL)
        return;

    DNode *left = head;
    DNode *right = head;

    // Move right to end
    while (right->next != NULL)
        right = right->next;

    int found = 0;
    while (left != NULL && right != NULL && left != right && right->next != left)
    {
        int current_sum = left->data + right->data;
        if (current_sum == sum)
        {
            printf("Pair found: (%d, %d)\n", left->data, right->data);
            found = 1;
            left = left->next;
            right = right->prev;
        }
        else if (current_sum < sum)
            left = left->next;
        else
            right = right->prev;
    }

    if (!found)
        printf("No pair found with sum %d.\n", sum);
}

DNode *rotate(DNode *head, int k)
{
    if (head == NULL || k == 0)
        return head;

    int len = get_length(head);
    k = k % len; // Handle k > length
    if (k == 0)
        return head;

    DNode *current = head;
    int count = 1;

    // Move to the kth node
    while (count < k && current != NULL)
    {
        current = current->next;
        count++;
    }

    if (current == NULL || current->next == NULL)
        return head;

    DNode *kthNode = current;

    // Go to end of list
    while (current->next != NULL)
        current = current->next;

    // Connect tail to head
    current->next = head;
    head->prev = current;

    head = kthNode->next;
    head->prev = NULL;
    kthNode->next = NULL;

    return head;
}

DNode *delete_duplicates(DNode *head)
{
    if (head == NULL)
        return NULL;

    DNode *ptr1 = head;
    DNode *ptr2, *duplicate;

    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;
        while (ptr2->next != NULL)
        {
            if (ptr1->data == ptr2->next->data)
            {
                duplicate = ptr2->next;
                ptr2->next = duplicate->next;

                if (duplicate->next != NULL)
                    duplicate->next->prev = ptr2;

                free(duplicate);
            }
            else
            {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
    return head;
}

void max_sum_sublist(DNode *head)
{
    if (head == NULL)
        return;

    int max_so_far = head->data;
    int current_max = head->data;
    DNode *current = head->next;

    while (current != NULL)
    {
        if (current_max + current->data > current->data)
            current_max += current->data;
        else
            current_max = current->data;

        if (current_max > max_so_far)
            max_so_far = current_max;

        current = current->next;
    }
    printf("Maximum Sum Sublist Value: %d\n", max_so_far);
}

int is_palindrome(DNode *head)
{
    if (head == NULL)
        return 1;

    DNode *left = head;
    DNode *right = head;

    // Move right to end
    while (right->next != NULL)
        right = right->next;

    while (left != right && right->next != left)
    {
        if (left->data != right->data)
            return 0; // Not a palindrome

        left = left->next;
        right = right->prev;
    }
    return 1;
}

DNode *merge_sorted(DNode *first, DNode *second)
{
    if (!first)
        return second;
    if (!second)
        return first;

    // Pick the smaller value as head
    if (first->data < second->data)
    {
        first->next = merge_sorted(first->next, second);
        if (first->next)
            first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge_sorted(first, second->next);
        if (second->next)
            second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

DNode *swap_nodes(DNode *head, int pos1, int pos2)
{
    if (pos1 == pos2 || head == NULL)
        return head;

    // Ensure pos1 < pos2 for easier handling
    if (pos1 > pos2)
    {
        int t = pos1;
        pos1 = pos2;
        pos2 = t;
    }

    DNode *node1 = head, *node2 = head;

    // Find Node 1
    for (int i = 1; i < pos1 && node1 != NULL; i++)
        node1 = node1->next;
    // Find Node 2
    for (int i = 1; i < pos2 && node2 != NULL; i++)
        node2 = node2->next;

    if (node1 == NULL || node2 == NULL)
    {
        printf("Invalid positions.\n");
        return head;
    }

    // Pointers to surrounding nodes
    DNode *prev1 = node1->prev;
    DNode *next1 = node1->next;
    DNode *prev2 = node2->prev;
    DNode *next2 = node2->next;

    // Case: Adjacent nodes
    if (node1->next == node2)
    {
        if (prev1)
            prev1->next = node2;
        if (next2)
            next2->prev = node1;

        node2->prev = prev1;
        node2->next = node1;
        node1->prev = node2;
        node1->next = next2;
    }
    else
    {
        // Not adjacent
        if (prev1)
            prev1->next = node2;
        if (next1)
            next1->prev = node2;

        if (prev2)
            prev2->next = node1;
        if (next2)
            next2->prev = node1;

        node1->prev = prev2;
        node1->next = next2;
        node2->prev = prev1;
        node2->next = next1;
    }

    // Update Head if necessary
    if (head == node1)
        return node2;
    if (head == node2)
        return node1;

    return head;
}

void set_random_pointers(DNode *head)
{
    if (!head)
        return;
    srand(time(0));
    int len = get_length(head);
    DNode *curr = head;
    while (curr)
    {
        int r = rand() % (len + 1); // +1 to allow NULL random
        if (r == len)
        {
            curr->random = NULL;
        }
        else
        {
            DNode *target = head;
            for (int i = 0; i < r; i++)
                target = target->next;
            curr->random = target;
        }
        curr = curr->next;
    }
}

DNode *clone_list(DNode *head)
{
    if (head == NULL)
        return NULL;

    DNode *curr = head;

    // Insert copy nodes between original nodes
    while (curr != NULL)
    {
        DNode *temp = create_dnode(curr->data);
        temp->next = curr->next;
        curr->next = temp;
        temp->prev = curr;
        curr = temp->next;
    }

    // Copy random pointers
    curr = head;
    while (curr != NULL)
    {
        if (curr->next != NULL)
        {
            curr->next->random = (curr->random != NULL) ? curr->random->next : NULL;
        }
        curr = curr->next->next;
    }

    // Separate the lists
    DNode *original = head;
    DNode *copy = head->next;
    DNode *copy_head = copy;

    while (original != NULL && copy != NULL)
    {
        original->next = (original->next != NULL) ? original->next->next : NULL;
        copy->next = (copy->next != NULL) ? copy->next->next : NULL;

        original = original->next;
        copy = copy->next;
    }

    // Fix prev pointers for the copy list (simple traversal)
    curr = copy_head;
    curr->prev = NULL;
    while (curr->next != NULL)
    {
        curr->next->prev = curr;
        curr = curr->next;
    }

    return copy_head;
}

int main()
{
    DNode *head = NULL;
    int choice, val, k, pos1, pos2;

    while (1)
    {
        printf("\nDoubly Linked List Operations\n");
        printf("1. Insert Node at End\n");
        printf("2. Display List\n");
        printf("3. Reverse List\n");
        printf("4. Find Pair with Sum (Two Sum)\n");
        printf("5. Rotate List by K\n");
        printf("6. Delete Duplicates\n");
        printf("7. Find Max Sum Sublist\n");
        printf("8. Check Palindrome\n");
        printf("9. Swap Nodes at Positions\n");
        printf("10. Clone List (with Random Pointers)\n");
        printf("11. Merge with another sorted list (Demo)\n");
        printf("12. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &val);
            head = insert_end(head, val);
            break;
        case 2:
            display_dlist(head);
            break;
        case 3:
            head = reverse_dlist(head);
            printf("List reversed.\n");
            break;
        case 4:
            printf("Enter sum to find: ");
            scanf("%d", &val);
            printf("Note: Assuming list is sorted for Two-Pointer technique.\n");
            find_two_sum(head, val);
            break;
        case 5:
            printf("Enter K: ");
            scanf("%d", &k);
            head = rotate(head, k);
            printf("List rotated.\n");
            break;
        case 6:
            head = delete_duplicates(head);
            printf("Duplicates deleted.\n");
            break;
        case 7:
            max_sum_sublist(head);
            break;
        case 8:
            if (is_palindrome(head))
                printf("List IS a palindrome.\n");
            else
                printf("List is NOT a palindrome.\n");
            break;
        case 9:
            printf("Enter Position 1 and Position 2: ");
            scanf("%d %d", &pos1, &pos2);
            head = swap_nodes(head, pos1, pos2);
            printf("Nodes swapped.\n");
            break;
        case 10:
            set_random_pointers(head);
            printf("Random pointers assigned arbitrarily.\n");
            display_dlist(head);
            DNode *cloned = clone_list(head);
            printf("Cloned List: ");
            display_dlist(cloned);
            free_dlist(cloned);
            break;
        case 11:
        {
            DNode *h1 = NULL;
            DNode *h2 = NULL;
            h1 = insert_end(h1, 1);
            h1 = insert_end(h1, 3);
            h1 = insert_end(h1, 5);
            h2 = insert_end(h2, 2);
            h2 = insert_end(h2, 4);
            h2 = insert_end(h2, 6);
            printf("List 1: ");
            display_dlist(h1);
            printf("List 2: ");
            display_dlist(h2);
            DNode *merged = merge_sorted(h1, h2);
            printf("Merged: ");
            display_dlist(merged);

            free_dlist(merged);
        }
        break;
        case 12:
            free_dlist(head);
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}