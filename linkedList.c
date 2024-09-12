#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct Queue {
    Node *front, *rear;
} Queue;

// Function to create a new node
Node* createNode(int new_data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;  // Initialize prev to NULL
    return new_node;
}

// Function to create a new queue
Queue *createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to add an element to the queue
void enqueue(Queue *q, int new_data) {
    Node *new_node = createNode(new_data);
    if (checkInQueue(q, new_data)){
        removeIndex(q, new_data);
    }
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return;
    }
    q->rear->next = new_node;
    new_node->prev = q->rear;
    q->rear = new_node;
}

// Function to remove an element from the queue
int dequeue(Queue *q) {
    if (q->front == NULL) {
        return -1;  // Queue is empty
    }

    Node *temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;  // Queue is now empty
    } else {
        q->front->prev = NULL;
    }

    free(temp);
    return data;
}

// Function to get the front element of the queue
int getFront(Queue *q) {
    if (q->front == NULL) {
        return INT_MIN;  // Queue is empty
    }
    return q->front->data;
}

// Function to get the rear element of the queue
int getRear(Queue *q) {
    if (q->rear == NULL) {
        return INT_MIN;  // Queue is empty
    }
    return q->rear->data;
}

// Function to remove a node with a specific index value
void removeIndex(Queue *q, int index) {
    Node *temp = q->front;
    while (temp != NULL) {
        if (temp->data == index) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                q->front = temp->next;  // Removing front node
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            } else {
                q->rear = temp->prev;  // Removing rear node
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

int checkInQueue(Queue * q, int index){
    Node * temp = q->front;
    while (temp != NULL){
        if (temp->data == index){
            return 1;
        }
        temp=temp->next;
    }
    return -1;
}