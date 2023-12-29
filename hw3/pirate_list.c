/*
    pirate_list.c
    Annabelle Huang
    CPSC 223 HW 2
    March 10th, 2023
    Purpose: defining functions that are declared in pirate_list.h
    so that hookbook.c may use these functions to create a
    list of pirate names given by the input file that is sorted 
    alphabetically.
*/ 
#include <stdlib.h>
#include <stdio.h>

#include "pirate_list.h"

#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

// implementation of type pirate
struct implementation {
    size_t capacity;
    size_t length;
    pirate *arr;
};

// Parameters: no parameters 
// Returns: a newly malloced pirate_list * 
// Purpose: create a new pirate_list 
pirate_list *list_create() {
    pirate_list *newlst = (pirate_list *) malloc(sizeof(pirate_list));
    newlst->capacity = INITIAL_CAPACITY;
    newlst->length = 0;
    newlst->arr = (pirate *) malloc(sizeof(pirate) * INITIAL_CAPACITY);
    return newlst;
}

// Parameters: pirate_list * called pirates 
// Returns: nothing
// Purpose: Check if the actual number of pirates
// in the array is "too large"; if it is, increase
// the capacity of the array by a factor of RESIZE_FACTOR.
// If the array capacity was changed, print to stderr 
// the string "Expand to ", followed by the new capacity 
// of the list and a newline. 
// If the capacity was not changed, do nothing.
void list_expand_if_necessary(pirate_list* pirates) { 
    while (pirates->length > pirates->capacity) {
        pirates->capacity = pirates->capacity * RESIZE_FACTOR;
        fprintf(stderr, "Expand to %zu\n", pirates->capacity);
    }
}

// Parameters: pirate_list * called pirates 
// Returns: nothing
// Purpose: Check if the actual number of 
// pirates in the array is "too small"; 
// if it is, decrease the capacity of the 
// array by a factor of RESIZE_FACTOR.
// If the array capacity was changed, print 
// to stderr the string "Contract to " 
// followed by the new capacity of the list
// If the capacity was not changed, do nothing.
void list_contract_if_necessary(pirate_list* pirates) { 
    while ((pirates->capacity / RESIZE_FACTOR) >= INITIAL_CAPACITY) {
        pirates->capacity = pirates->capacity / RESIZE_FACTOR;
        fprintf(stderr, "Contract to %zu\n", pirates->capacity);
    }
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx) {
    // returns NULL if the given index is out of bounds
    if (idx >= pirates->capacity) {
        return NULL;
    }
    // if the insert index is 0, at the beginning of the array
    // then malloc space for the pirate at 0th index of pirates_list
    // and copy given pirate's name to the space
    if (idx == 0) {
        pirates->arr[0].name = (char *) malloc(sizeof(char) * strlen(p->name) + 1);
        strcpy(pirates->arr[0].name, p->name);
        pirates->length ++;
        return NULL;
    }
    // check if there is pirate of same name
    // if there is, returns pointer to the pirate
    for (int i = 0 ; i < (pirates->length) ; i ++) { 
        if (strcmp(p->name, pirates->arr[i].name) == 0){ 
            return p;
        }
    }
    // malloc space for new pirate and 
    // copy the given pirate's name to the destination
    pirates->arr[idx].name = (char *) malloc(sizeof(char) * 66);
    strcpy(pirates->arr[idx].name, p->name);
    pirates->length ++;
    return NULL;
}