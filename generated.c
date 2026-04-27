#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next; // Renamed from next1 for clarity and convention
};

void insertAtFront(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        perror("Memory allocation failed"); // Use perror for better error reporting
        exit(EXIT_FAILURE); // Exit program on allocation failure
    }
    new_node->data = new_data;
    new_node->next = (*head_ref); // Use the renamed 'next' pointer
    (*head_ref) = new_node;
}

int main() {
    struct Node* head = NULL;

    insertAtFront(&head, 10);
    insertAtFront(&head, 20);
    insertAtFront(&head, 30);

    printf("Linked list elements: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next; // Use the renamed 'next' pointer
    }
    printf("\n");

    // Free allocated memory
    current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next; // Use the renamed 'next' pointer
        free(temp);
    }
    head = NULL; // Ensure head is NULL after freeing

    return 0;
}
