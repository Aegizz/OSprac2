#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.c"

// Define the Circle structure
typedef struct Circle {
    Node *curr;
    Node *tail;
} Circle;

// Create a new Circle
Circle *createCircle() {
    Circle *c = (Circle *)malloc(sizeof(Circle));
    c->curr = c->tail = NULL;
    return c;
}

// Find a node with a specific value
Node *findValue(Circle *c, int index) {
    if (c->curr == NULL) return NULL; // Return NULL if the list is empty
    
    Node *temp = c->curr;
    do {
        if (temp->data == index) {
            return temp;
        }
        temp = temp->next;
    } while (temp != c->curr);
    
    return NULL;
}

// Insert a new node into the circle
Node *insertNode(Circle *c, int data) {
    Node *new_node;
    
    // Check if the node with the given value already exists
    Node *existing_node = findValue(c, data);
    if (existing_node != NULL) {
        c->curr = existing_node;
        c->tail = existing_node->prev;
        return c->curr;
    }
    
    // Create a new node
    new_node = createNode(data);
    
    // If the list is empty
    if (c->curr == NULL && c->tail == NULL) {
        new_node->next = new_node;
        new_node->prev = new_node;
        c->curr = c->tail = new_node;
        return c->curr;
    }
    
    // Insert new_node before curr
    new_node->next = c->curr;
    new_node->prev = c->tail;
    
    // Update links
    c->tail->next = new_node;
    c->curr->prev = new_node;
    c->tail = new_node; // Update tail to new_node

    return c->tail; 
}

// Update the data of the current node
void updateCurr(Circle *c, int new_data) {
    if (c->curr != NULL) {
        c->curr->data = new_data;
    }
}

// Rotate the circle
Node *rotate(Circle *c) {
    if (c->curr != NULL && c->tail != NULL) {
        c->curr = c->curr->next;
        c->tail = c->tail->next;
        return c->curr;
    }
    return NULL;
}