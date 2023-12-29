/* 
 * Station.cpp
 * CPSC 223 HW 4
 * Annabelle Huang
 * April 5th, 2023
 * Implementation of the Station class
 */

#include "Station.h"
#include <iostream>
#include <fstream>

// Constructor
Station::Station(){
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access){
    name = input_name;
    if (input_access) {
        access = true;
    }
    else {
        access = false;
    }
}

// Function: isEqual(Station s)
// Input: Station s
// Returns: boolean value
// Does: returns true if s elements are equal to elements 
// of Station that invoked isEqual, otherwise false
bool Station::isEqual(Station s){
    if (s.name == name && s.access == access) {
        return true;
    }
    return false;
}

// Function: print(ostream &outfile)
// Input: ostream &outfile
// Returns: nothing
// Does: writes the name and accessibility of the Station
// that invoked print
void Station::print(ostream &outfile) {
    if (access == true) {
        outfile << name << " A";
    }
    else {
        outfile << name << " U";
    }
    return;
}