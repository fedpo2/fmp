// Copyright (c) 2023 Federico Polidoro. All Rights Reserved.
#include "linkedList.h"

void print_list(struct linked_node *p){
    while(p != NULL){
        printf("%s\n ",p->value);
        p = p->next;
    }
}

char* get_value(struct linked_node *p ,int index){
    if( index == 0 ) return p->value;
    while(index != 0){
        if(p->next != NULL && p != NULL){
            p = p->next;
            --index;
        }else{
            return "OUT OF RANGE";
        }
    }
    return p->value;
}

void top_push(struct linked_node** head, char* str){
    struct linked_node* new_head;
    new_head = (struct linked_node*)malloc(sizeof(struct linked_node));
    new_head->value = str;
    new_head->next = *head;
    *head = new_head;
}

void end_push(struct linked_node** head, char* str){
    if (*head == NULL){
        struct linked_node* new_head = malloc(sizeof(struct linked_node));
        new_head->value = str;
        *head = new_head;
        return;
    }

    struct linked_node* new_head = malloc(sizeof(struct linked_node));
    new_head->value = str;

    struct linked_node* p = *head;
    while (p->next != NULL){
        p = p->next;
    }

    p->next = new_head;
}

char* top_pop(struct linked_node** head){
    char* devolucion = "head es nulo";
    if(*head == NULL) return devolucion;
    if((*head)->value == NULL) return devolucion;

    struct linked_node* nnode = (*head)->next;
    devolucion = (*head)->value;
    free(*head);
    *head = nnode;
    return devolucion;
}

char* end_pop(struct linked_node** head){
    char* devolucion = "end es nulo";

    struct linked_node* lnode = *head;

    while(lnode->next != NULL){
        lnode = lnode->next;
    }

    if(lnode != NULL){
        devolucion = lnode->value;
        free(lnode);
    }
    return devolucion;
}
