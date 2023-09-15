// Copyright (c) 2023 Federico Polidoro. All Rights Reserved.
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>

struct linked_node {
    char* value;
    struct linked_node* next;
};

void print_list(struct linked_node*);

char* get_value(struct linked_node* ,int); // este devuelve un valor dentro del

void top_push(struct linked_node**, char*); // ingreso al inicio o final
void end_push(struct linked_node**, char*);

char* top_pop(struct linked_node**); // elimino al inicio o final.
char* end_pop(struct linked_node**);

#endif // LINKEDLIST_H_
