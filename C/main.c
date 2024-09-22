#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node {
    struct Node* next;
    struct Node* prev;
    char* data;
};

struct Node* CreateNodeOnHeap(const char* const data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = malloc(strlen(data));
    strcpy(newNode->data, data);
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}


struct DoublyLinkedList {
    struct Node* head;
};

struct DoublyLinkedList CreateEmptyDoublyLinkedList() {
    struct DoublyLinkedList dll = {NULL};
    return dll;
}

struct Node* Find(
    const struct DoublyLinkedList* const dll, 
    char data[]) 
{
    struct Node* cur = dll->head;

    while (cur != NULL) {
        if (!strcmp(cur->data, data))
            return cur;
        cur = cur->next;
    }

    return NULL;
}

void InsertAfter(
    struct DoublyLinkedList* const dll, 
    struct Node* const node, 
    char data[]) 
{
    struct Node* newNode = CreateNodeOnHeap(data);

    if (node == NULL) {
        if (dll->head == NULL) {
            dll->head = newNode;
        }
        else {
            struct Node* cur = dll->head;

            while (cur->next != NULL) {
                cur = cur->next;
            }

            cur->next = newNode;
            newNode->prev = cur;
        }
        return;
    }

    newNode->prev = node;
    if (node->next != NULL) {
        node->next->prev = newNode;
        newNode->next = node->next;
    }
    node->next = newNode;
}

void InsertBefore(
    struct DoublyLinkedList* const dll, 
    struct Node* const node, 
    char data[]) 
{
    struct Node* newNode = CreateNodeOnHeap(data);

    if (node == NULL || dll->head == node) {
        if (dll->head != NULL) {
            newNode->next = dll->head;
            dll->head->prev = newNode;
        }
        dll->head = newNode;
        return;
    }

    newNode->next = node;
    newNode->prev = node->prev;
    node->prev->next = newNode;
    node->prev = newNode;
}

void Print(const struct DoublyLinkedList* const dll) {
    struct Node* cur = dll->head;

    printf("DoublyLinkedList{\n");
    while (cur != NULL) {
        printf("\t");
        printf(cur->data);
        printf("\n");
        cur = cur->next;
    }
    printf("}\n");
}

void Delete(struct DoublyLinkedList* const dll, struct Node* const node) {
    if (node == NULL) {
        if (dll->head == NULL) return;

        struct Node* cur = dll->head;

        while (cur->next != NULL)
            cur = cur->next;

        while (cur != NULL) {
            struct Node* toBeDeleted = cur;
            cur = cur->prev;

            free(toBeDeleted->data);
            free(toBeDeleted);
        }       

        dll->head = NULL;
        return;
    }

    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (dll->head == node)
        dll->head = node->next;

    free(node->data);
    free(node);
}


int main(int argc, char const *argv[]) {
    struct DoublyLinkedList myDll = CreateEmptyDoublyLinkedList();

    InsertAfter(&myDll, NULL, "Shayan");
    Print(&myDll);

    InsertAfter(&myDll, NULL, "Salman");
    Print(&myDll);

    struct Node* salman = Find(&myDll, "Salman");
    InsertBefore(&myDll, salman, "Hassaan");
    Print(&myDll);

    InsertBefore(&myDll, NULL, "Zubair");
    Print(&myDll);

    struct Node* zubair = Find(&myDll, "Zubair");
    InsertAfter(&myDll, zubair, "Mussarat");
    Print(&myDll);

    InsertBefore(&myDll, zubair, "My Family:");
    Print(&myDll);
    
    Delete(&myDll, zubair->prev);
    Print(&myDll);
    
    Delete(&myDll, NULL);
    Print(&myDll);

    return 0;
}
