/*
    Life.c
    Annabelle Huang
    CPSC 223 HW 2
    February 11th, 2023
    Purpose: implement functions declared in Life.h
*/ 

#include <stdio.h>
#include <stdbool.h>
#include "Life.h"

void nextArray(int array[], int size) {
    int arrayCopy[size];
    // makes a copy of the array passed into the function
    for (int i = 0 ; i < size ; i ++) {
        arrayCopy[i] = array[i];
    } 
    // checks whether cell with index i should die or not
    // depending on the two given rules 
    for (int i = 0 ; i < size ; i ++) {
        if (i == 0 && arrayCopy[i] == 0) { // if first cell is dead
            continue;
        }
        else if (i == 0 && arrayCopy[i] == 1) { // if first cell is alive
            if (arrayCopy[i + 1] == 0) {
                array[i + 1] = 1;
            }
            else {
                continue;
            }
        }
        else if (i == (size - 1) && arrayCopy[i] == 0) { // if last cell is dead
            continue;
        }
        else if (i == (size - 1) && arrayCopy[i] == 1) { // if last cell is alive
            if (arrayCopy[size - 2] == 0) {
                array[size - 2] = 1;
            }
            else {
                continue;
            }
        }
        else { // check cells with index from 1 to (size - 1)
            if (arrayCopy[i] == 0) { // if cell is dead 
                continue;
            }
            else if (shouldDie(arrayCopy, i, size)) {
                array[i] = 0;
            }
            else { // cell is alive and there aren't two alive neighboring cells
                if (arrayCopy[i + 1] == 0) {
                    array[i + 1] = 1;
                }
                if (arrayCopy[i - 1] == 0) {
                    array[i - 1] = 1;
                }
            }
        }
    }
}
// Parameters: copy of initial value aray, 
//             cell index to be checked and size of array
// Purpose: determines whether a cell should die or not 
// Returns: true if there are two alive neighboring cells 
//          false if there aren't two alive neightboring cells
bool shouldDie(int arrayCopy[], size_t index, size_t size) { 
    if (arrayCopy[index - 1] == 1 && arrayCopy[index + 1] == 1) {
        return true;
    }
    else { 
        return false; 
    }
}
// Parameters: copy of initial value aray, 
//             cell index to be checked and size of array
// Purpose: determines whether a cell is alive or not
// Returns: true if the cell at given index is alive and false if dead
bool isAlive(int array[], size_t index, size_t size) {
    if (array[index] == 1) {
        return true;
    }
    else {
        return false;
    }
}

