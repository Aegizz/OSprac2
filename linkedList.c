#include <limits.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node * next;
    struct Node * prev;

} Node;

typedef struct Queue{
    Node * front, *rear;
} Queue;

Node* createNode(int new_data){
    Node * new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;

    return new_node;
}
Queue * createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue * q, int new_data){
    Node * new_node = createNode(new_data);
    if (q->rear == NULL){
        q->front = q->rear = new_node;
        return;
    }
    q->rear->next = new_node;
    new_node->prev = q->rear;
    q->rear = new_node;
}

int dequeue(Queue* q){
    if (q->front == NULL && q->rear == NULL){
        return -1;
    }

    Node * temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL){
        q->rear = NULL;
    }

    free(temp);
    return data;
}

int getFront(Queue * q){
    if (q->front == NULL && q->rear == NULL){
        return INT_MIN;
    }
    return q->front->data;
}

int getRear(Queue * q){
    if (q->front == NULL && q->rear == NULL){
        return INT_MIN;
    }
    return  q->rear->data;
}

void removeIndex(Queue * q, int index){
    Node * temp = q->front;
    while (temp != NULL){
        if (temp->data == index){
            temp->prev->next = temp->next;
            free(temp);
            return;
        }
        temp = temp->next;
    }
    return;
}