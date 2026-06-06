#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a new node at the front of the linked list
void insertAtFront(struct Node** head_ref, int new_data) {
    // 1. Allocate node
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    // Check if memory allocation was successful
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // 2. Put in the data
    new_node->data = new_data;

    // 3. Make next of new node as head
    new_node->next = (*head_ref);

    // 4. Move the head to point to the new node
    (*head_ref) = new_node;
}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Main function to test the insertion at front
int main() {
    // Start with the empty list
    struct Node* head = NULL;

    printf("Original list: ");
    printList(head);

    // Insert 6 at the front. List becomes 6->NULL
    insertAtFront(&head, 6);
    printf("After inserting 6: ");
    printList(head); // Output: 6

    // Insert 7 at the front. List becomes 7->6->NULL
    insertAtFront(&head, 7);
    printf("After inserting 7: ");
    printList(head); // Output: 7 6

    // Insert 1 at the front. List becomes 1->7->6->NULL
    insertAtFront(&head, 1);
    printf("After inserting 1: ");
    printList(head); // Output: 1 7 6

    // Insert 4 at the front. List becomes 4->1->7->6->NULL
    insertAtFront(&head, 4);
    printf("After inserting 4: ");
    printList(head); // Output: 4 1 7 6

    // Free the allocated memory to prevent memory leaks
    struct Node* current = head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // Optional: set head to NULL after freeing

    return 0;
}