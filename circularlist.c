#include <limits.h>
#include <stdio.h>
#include "linkedList.c"


typedef struct Circle{
    struct Node * curr;
    struct Node * tail;
} Circle;


Circle * createCircle(void){
    Circle * c = (Circle*)malloc(sizeof(Circle));
    c->curr = NULL;
    c->tail = NULL;
    return c;
}

void insertNode(Circle * c, int data){
    Node * new_node = createNode(data);
    if (c->curr == NULL && c->tail == NULL){
        c->curr = c->tail = new_node;
        return;
    }
    new_node->next = c->curr;
    new_node->prev = c->tail;


    c->curr->prev = new_node;
    c->curr = new_node;

    c->tail->next = c->curr;
    return; 
}

void updateCurr(Circle * c, int new_data){
    c->curr->data = new_data;
}

Node * findValue(Circle * c, int index){
    while (c->curr != NULL && c->tail != NULL){
        if (c->curr == index){
            return c->curr;
        }
        c->curr = c->curr->next;
        c->tail = c->tail->next;
    }
    return NULL;
}

Node * rotate(Circle * c){
    if (c->curr != NULL && c->tail != NULL){
        c->curr = c->curr->next;
        c->tail = c->tail->next;
        return c->curr;
    }
    return NULL;
}