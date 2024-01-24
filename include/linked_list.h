// Copyright 2023 <Seres67>

#ifndef FRONTEND_LINKED_LIST_H
#define FRONTEND_LINKED_LIST_H

#include <stddef.h>

typedef struct linked_list
{
    void *data;
    struct linked_list *next;
    struct linked_list *prev;
} linked_list_t;

linked_list_t *linked_list_new(void *data);
void linked_list_delete(linked_list_t *list);
linked_list_t *linked_list_push(linked_list_t *list, void *data);
void *linked_list_pop(linked_list_t *list);
void *linked_list_remove(linked_list_t *list, size_t index);

#endif // !FRONTEND_LINKED_LIST_H
