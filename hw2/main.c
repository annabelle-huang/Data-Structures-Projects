/*
    main.c
    Annabelle Huang
    CPSC 223 HW 2
    February 11th, 2023
    Purpose: main for running program of life
*/ 

#include <stdio.h>
#include <stdlib.h>
#include "Life.h"
#include <string.h>
#include <math.h>

// Parameters: command line inputs 
// Returns: the initial cell sequence and subsequent simulations 
// with given number of timesteps
// Purpose: print timestep number of sequences of cell 
int main(int argc, char* argv[]) {
    if (argc < 4) {
        return 1;
    }
    int time_steps = atoi(argv[1]); 
    int game_size = atoi(argv[2]); 
    int start[game_size];
    // checks if all characters of the first argument are integers
    // if not, returns nonzero status code
    for (int i = 0 ; i < strlen(argv[1]) ; i ++) { 
        if (argv[1][i] != '0' && argv[1][i] != '1' && argv[1][i] != '2' &&
            argv[1][i] != '3' && argv[1][i] != '4' && argv[1][i] != '5' &&
            argv[1][i] != '6' && argv[1][i] != '7' && argv[1][i] != '8' &&
            argv[1][i] != '9') {
                return 1;
        }
    } 
    // checks if all characters of second argument are integers
    // if not, returns nonzero status code
    for (int i = 0 ; i < strlen(argv[2]) ; i ++) { 
        if (argv[2][i] != '0' && argv[2][i] != '1' && argv[2][i] != '2' &&
            argv[2][i] != '3' && argv[2][i] != '4' && argv[2][i] != '5' &&
            argv[2][i] != '6' && argv[2][i] != '7' && argv[2][i] != '8' &&
            argv[2][i] != '9') {
                return 1;
        }
    }
    // checks if timesteps is a negative number, if game size is a nonpositive 
    // number, and if game size is greater than the length of argument 3
    // if it is, then returns nonzero status code
    if (time_steps < 0 || game_size <= 0 || game_size > strlen(argv[3])) {
        return 1;
    }
    // copies the input array to another array called start, while 
    // checking if there are non-integer characters. If there are, 
    // return nonzero status code
    for (int i = 0 ; i < game_size ; i ++) { 
        if (argv[3][i] == '0') {
            start[i] = 0;    
        }
        else if (argv[3][i] == '1') {
            start[i] = 1;
        }
        else {
            return 1;
        }    
    }
    printf("%-33s", "Initial values");
    printf("[");
    // prints out the initial value in specified format
    for (int i = 0 ; i < game_size ; i ++) {
        printf("%d", start[i]);
        if (i != (game_size - 1)) {
            printf(", ");
        }
    }
    printf("]\n");
    // prints the values after each timestep in specified format
    for (int t = 0 ; t < time_steps ; t ++) {
        nextArray(start, game_size);
        printf("Values after timestep %d", t+1);
        if ((t + 1) < 10) {
            printf("%-10s", "");
        }
        if ((t + 1) >= 10 && (t + 1) < 100) {
            printf("%-9s", "");
        }
        if ((t + 1) >= 100 && (t + 1) < 1000) {
            printf("%-8s", "");
        }
        if ((t + 1) >= 1000 && (t + 1) < 10000) {
            printf("%-7s", "");
        }
        if ((t + 1) >= 10000 && (t + 1) < 100000) {
            printf("%-6s", "");
        }
        if ((t + 1) >= 100000 && (t + 1) < 1000000) {
            printf("%-5s", "");
        }
        if ((t + 1) >= 1000000 && (t + 1) < 10000000) {
            printf("%-4s", "");
        }
        if ((t + 1) >= 10000000 && (t + 1) < 100000000) {
            printf("%-3s", "");
        }
        if ((t + 1) >= 100000000 && (t + 1) < 1000000000) {
            printf("%-2s", "");
        }
        if ((t + 1) >= 1000000000 && (t + 1) < 10000000000) {
            printf("%-1s", "");
        }
        printf("[");
        for (int i = 0 ; i < game_size ; i ++) {
            printf("%d", start[i]);
            if (i != (game_size - 1)) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
