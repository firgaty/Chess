//
// Created by firgaty on 13/03/17.
//

#include "IntArray.hpp"
#include <iostream>

IntArray::IntArray() {
    m_moves[0] = -1;
    this->m_length = 0;
}
IntArray::IntArray(int *array) {
    if(array[0] == -1)  IntArray();
    else {

    }
}


// GETTERS & SETTERS

int* IntArray::getMoves() const {
    return this->m_moves;
}
int IntArray::length() const {
    return this->m_length;
}
bool IntArray::add(int val) {
    this->at(this->m_length) = val;
    this->at(this->m_length + 1) = -1;
    this->m_length ++;
}
int& IntArray::at(int index) {
    return this->m_moves[index];
}
int IntArray::getAt(int index) const{
    return this->m_moves[index];
}

// OPERATOR.

IntArray operator+(IntArray const& a, IntArray const& b) {
    IntArray out;
    for(int i(0); i < a.length(); i ++) {
        out.add(a.getAt(i));
    }
    for(int i(0); i < b.length(); i++) {
        out.add(a.getAt(i));
    }
    return out;
}

IntArray& IntArray::operator+=(IntArray const& a) {
    for(int i(0); i < a.length(); i++){
        this->add(a.getAt(i));
    }
    return *this;
}