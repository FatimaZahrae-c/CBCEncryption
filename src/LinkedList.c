#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "linkedlist.h"

Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erreur d'allocation mémoire pour le nœud");
        return NULL;
    }
    newNode->data = strdup(data); // Allouer et copier la chaîne
    newNode->next = NULL;
    return newNode;
}

Node* insertNode(Node* head, const char* data) {
    Node* newNode = createNode(data);
    if (!newNode) return head;

    if (head == NULL) {
        return newNode;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}
void displayList(Node* head) {
    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }

    Node* temp = head;
    while (temp) {
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
Node* deleteNode(Node* head, const char* value) {
    if (head == NULL) return NULL;

    // Si le nœud à supprimer est le premier
    if (strcmp(head->data, value) == 0) {
        Node* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
        return head;
    }

    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL && strcmp(temp->data, value) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Chaine '%s' introuvable dans la liste", value);
        return head;
    }
    prev->next = temp->next;
    free(temp->data);
    free(temp);
    return head;
}
