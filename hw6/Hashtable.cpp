/**
 * Hashtable.cpp
 *
 *      Implementation of Hashtable, using chaining.
 *      Interface mostly follows std::unordered_map
 *
 * Alan Weide
 * CPSC 223
 * Spring 2023
 *
 */
/*
 * Filename: Hashtable.cpp
 * CPSC 223 HW 6
 * Annabelle Huang
 * April 30th, 2023
 * Contains: Implementation of Hashtable for CPSC 223
 * Part of: Homework assignment "Grop" for CPSC 223
 */
#include "Hashtable.h"
#include <iostream>
#include <vector>
#include <functional>

template <class Value>
Hashtable<Value>::Hashtable() : Hashtable(initial_capacity) {}

// Parameterized constructor. Initialize table with `tablesize` buckets
template <class Value>
Hashtable<Value>::Hashtable(size_t tablesize)
{
    table.resize(tablesize);
}

template <class Value>
Value *Hashtable<Value>::insert(const Key &key, const Value &to_insert)
{
    Value* n = find(key);

    if (n == nullptr) { 
        table[index_of(key)].emplace_back(key, to_insert);
        num_of_elements++;
        if (load_factor() > max_load_factor)
            expand();
        return &(table[index_of(key)][table[index_of(key)].size()-1].val);
        
    }
    else { 
        *n = to_insert;
        return &(table[index_of(key)][table[index_of(key)].size()-1].val);
    }

    return nullptr;
}

/*
Purpose: to double the size of the table
Input: none
Output: none
*/
template <class Value>
void Hashtable<Value>::expand()
{
    Hashtable new_table(table.size()*2);
    for (size_t i = 0 ; i < table.size() ; i ++) {
        for (size_t j = 0 ; j < table[i].size() ; j ++) {
            new_table[table[i][j].key] = table[i][j].val;
        }
    }
    std::swap(*this, new_table);
}

template <class Value>
Value &Hashtable<Value>::at(const Key &key)
{
    Value *to_return = find(key);
    if (to_return == nullptr)
    {
        throw std::runtime_error("Key not in table");
    }
    return *to_return;
}

template <class Value>
const Value &Hashtable<Value>::at(const Key &key) const
{
    const Value *to_return = find(key);
    if (to_return == nullptr)
    {
        throw std::runtime_error("Key not in table");
    }
    return *to_return;
}

/*
Purpose: finds the value of the key
Input: key
Output: pointer to the value of the key
*/
template <class Value>
Value *Hashtable<Value>::find(const Key &key)
{
    for (size_t i = 0 ; i < table[index_of(key)].size() ; i++) {
        if (table[index_of(key)][i].key == key) 
        return &(table[index_of(key)][i].val);
    }
    return nullptr;
}

/*
Purpose: finds the value of the key
Input: key
Output: pointer to the value of the key
*/
template <class Value>
const Value *Hashtable<Value>::find(const Key &key) const
{
    for (size_t i = 0 ; i < table[index_of(key)].size() ; i++) {
        if (table[index_of(key)][i].key == key) 
        return &(table[index_of(key)][i].val);
    }
    return nullptr;
}

/*
Purpose: defines the bracket operator
Input: key
Output: returns pointer to value of key
*/
template <class Value>
Value &Hashtable<Value>::operator[](const Key &key)
{
    if (find(key) != nullptr) 
        return *find(key);
    return *insert(key, Value());
}

/*
Purpose: gives the index of key
Input: key
Output: index of key 
*/
template <class Value>
size_t Hashtable<Value>::index_of(const Key &key) const
{
    std::hash<Key> t;
    return t(key)%table.size();
}

/*
Purpose: gives the number of elements in the table
Input: none
Output: number of elements of table
*/
template <class Value>
size_t Hashtable<Value>::size() const
{
    return num_of_elements;
}

/*
Purpose: gives the load factor of the table
Input: none
Output: returns the load factor of the table
*/
template <class Value>
double Hashtable<Value>::load_factor() const
{
    return ((double) num_of_elements)/table.size();
}

// Explicit template specialization for "string"s
template class Hashtable<std::string>;

// Explicit template specialization for "Entry"s
#include "Entry.h"
template class Hashtable<std::vector<Entry>>;
