#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* nueva_lista = (List*) malloc(sizeof(List));
    if (nueva_lista == NULL) return NULL;
    nueva_lista->tail = NULL;
    nueva_lista->current = NULL;
    nueva_lista->head = NULL;
     return nueva_lista;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;
    Node * nuevo_nodo = createNode(data); 
    if (nuevo_nodo == NULL) return; 
    nuevo_nodo->next = list->head;
    if (list->head != NULL) list->head->prev = nuevo_nodo;
    else list->tail = nuevo_nodo;
    list->head = nuevo_nodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return;
    Node * nuevo_nodo = createNode(data);
    if (nuevo_nodo == NULL) return;
    nuevo_nodo->next = list->current->next;
    nuevo_nodo->prev = list->current;
    if (list->current->next != NULL) list->current->next->prev = nuevo_nodo;
    else list->tail = nuevo_nodo;
    list->current->next = nuevo_nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;
    Node * nodo_eliminar = list->current;
    void * dato = nodo_eliminar->data;
    if (nodo_eliminar->prev != NULL) nodo_eliminar->prev->next = nodo_eliminar->next;
    else list->head = nodo_eliminar->next;
    if (nodo_eliminar->next != NULL) nodo_eliminar->next->prev = nodo_eliminar->prev;
    else list->tail = nodo_eliminar->prev;
    list->current = nodo_eliminar->next;
    free(nodo_eliminar);
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}