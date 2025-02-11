#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// Prototypes
Node* createNode(const char* data);
Node* insertNode(Node* head, const char* data);
void displayList(Node* head);
Node* deleteNode(Node* head, const char* value);

#endif
