/*
    hookbook.c
    Annabelle Huang
    CPSC 223 HW 2
    March 10th, 2023
    Purpose: main for running HookBook
*/ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pirate_list.c"

// Parameters: command line inputs 
// Returns: the list of pirates names given in the 
// input file sorted alphabetically 
// Purpose: sort and return given pirate names alphabetically 
int main (int argc, char **argv) {
    if (argc == 2) {
        char line[66];
        char s[66];
        int count = 0;
        FILE *fp = fopen(argv[1], "r+");
        FILE *p = fopen(argv[1], "r+");
        if (fp == NULL) { // checks if you can open the file
            return 1;
        }
        while (fgets(line, 66, fp) != NULL) {
            line[strcspn(line, "\n")] = '\0';
            count ++;
        }
        // creating pirate_list pointer pirates
        // setting capacity and reallocating memory for array
        pirate_list *pirates = list_create();
        pirates->capacity = count;
        pirates->arr = (pirate *) realloc(pirates->arr, sizeof(pirate) * count);
        // reading the names from the file line by line and
        // inserting them into an array if they do not exist
        // already
        for (int i = 0 ; i < count ; i ++) {
            if (fgets(s, 66, p) == NULL)
                break;
            s[strcspn(s, "\n")] = '\0'; // gets line without \n
            pirate new_p;
            new_p.name = s;
            pirate *npp = &new_p;
            if (list_insert(pirates, npp, i) != NULL) {
                i--;
            }
        }
        char temp[66];
        // sorts pirates alphabetically
        for (int i = 0 ; i < (pirates->length - 1) ; i ++) {
            for(int j = i + 1 ; j < pirates->length ; j ++) {
                if (strcmp(pirates->arr[i].name, pirates->arr[j].name) > 0) {
                    strcpy(temp, pirates->arr[i].name);
                    strcpy(pirates->arr[i].name, pirates->arr[j].name);
                    strcpy(pirates->arr[j].name, temp);
                }
            }
        }
        pirates->capacity = 25;
        // check if the list needs to be expanded or contracted
        list_expand_if_necessary(pirates);
        list_contract_if_necessary(pirates);
        // print out the array
        for (int i = 0 ; i < pirates->length ; i ++) {
            printf("%s\n", pirates->arr[i].name);
        }
        fclose(fp);
        fclose(p);
        free(pirates->arr);
        free(pirates);
        return 0;
    }
    else {
        return 1;
    }
}