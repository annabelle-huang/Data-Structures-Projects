/* 
 * LinkedList.c
 * CPSC 223 HW 4
 * Annabelle Huang
 * April 5th, 2023
 * Implementation for Linked List of Green Line Extension Stations
 */


#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList() {
    length = 0;
    head = NULL;
    currPos = NULL;
}

// Destructor
LinkedList::~LinkedList() {
    makeEmpty();
}

// Assignment operator overloading
// Don't change anything here. This is needed for copying objects.
LinkedList & LinkedList::operator = (const LinkedList &l){
    NodeType *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    currPos = NULL;
    if (l.head == NULL)
        head = NULL;
    else{
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL){
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Input: nothing
// Returns: list's length
// Does: returns the length of the list
int LinkedList::getLength() const{
    return length;
}

// Input: nothing
// Returns: true if currPos is NULL
// Does: determines if currPos is NULL or not
bool LinkedList::isCurrPosNull() const{
    return currPos == NULL;    
}

// Input: Station
// Returns: nothing
// Does: Inserts the given station into the head of the list
void LinkedList::insertStation(Station s){
    NodeType *tp = new NodeType;
    tp->next = head;
    tp->info = s;
    head = tp;
    length++;
    return;
}

// Input: Station s
// Returns: nothing
// Does: Deletes the first instance of a station that is 
// in the list and isEqual to the one given as part of the input
void LinkedList::removeStation(Station s){
    NodeType *t;
    NodeType *c;
    c = head;
    while (c != NULL) {
        if (s.isEqual(c->info) && c == head) {
            head = c->next;
            if (c == currPos) {
                currPos = NULL;
            }
            delete c;
            length--;
            return;
        }
        if (s.isEqual(c->info) && c != head) {
            t->next = c->next;
            if (c == currPos) {
                currPos = NULL;
            }
            delete c;
            length--;
            return;
        }
        t = c;
        c = c->next; 
    }
    return;
}

// Input: nothing
// Returns: currPos's next station
// Does: return the next station in the list
Station LinkedList::getNextStation(){
    //TODO
    if (currPos == NULL){
        if(head == NULL){
            return Station();
        }

        currPos = head->next;
        return head->info;
    }
    NodeType *t;
    t = currPos;
    currPos = currPos->next;
    return t->info;
}

// Input: nothing
// Returns: nothing
// Does: sets currPos to NULL
void LinkedList::resetCurrPos(){
   currPos = NULL;
}

// Input: nothing
// Returns: nothing
// Does: delete all elements in the list and deallocate any allocated memory
void LinkedList::makeEmpty(){
    NodeType *c = head;
    NodeType *d;
    while (c != NULL) {
        d = c;
        c = c->next;
        delete d;
    }
    currPos = NULL;
    head = NULL;
    length = 0;
    return;
}

// Input: nothing
// Returns: nothing
// Does: Prints all the stations in the list in order from front to the end in a specified format
void LinkedList::print(ostream &out){
    int distance = getLength() - 1;
    NodeType *c = head;
    while (c->next != NULL) {
        c->info.print(out);
        out << " " << distance << " == ";
        distance--;
        c = c->next;
    }
    c->info.print(out);
    out << " " << distance << "\n";
    return;
}



