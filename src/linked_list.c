// Copyright 2023 <Seres67>

#include <linked_list.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

linked_list_t *linked_list_new(void *data)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    if (!list)
        return NULL;
    list->data = data;
    list->next = NULL;
    list->prev = NULL;
    return list;
}

void linked_list_delete(linked_list_t *list)
{
    linked_list_t *tmp = list;
    for (; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->prev)
            free(tmp->prev);
    }
    free(tmp->prev);
    free(tmp);
}

linked_list_t *linked_list_push(linked_list_t *list, void *data)
{
    linked_list_t *tmp = list;
    for (; tmp->next; tmp = tmp->next) {
    }
    tmp->next = malloc(sizeof(linked_list_t));
    if (!tmp->next)
        return NULL;
    tmp->next->data = data;
    tmp->next->next = NULL;
    tmp->next->prev = tmp;
    return list;
}

void *linked_list_pop(linked_list_t *list)
{
    void *data = NULL;
    if (list->next == NULL) {
        data = list->data;
        list->data = NULL;
    } else {
        linked_list_t *tmp = list;
        for (; tmp->next->next; tmp = tmp->next) {
        }
        data = tmp->next->data;
        free(tmp->next);
        tmp->next = NULL;
    }
    return data;
}

void *linked_list_remove(linked_list_t *list, size_t index)
{
    linked_list_t *tmp = list;
    for (size_t i = 0; i < index; ++i, tmp = tmp->next) {
    }
    void *data = tmp->data;
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    free(tmp);
    return data;
}
