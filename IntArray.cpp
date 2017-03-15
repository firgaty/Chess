//
// Created by firgaty on 13/03/17.
//

#include "IntArray.hpp"
#include <iostream>

IntArray::IntArray() {
    m_moves[0] = -1;
}

const int *IntArray::getM_moves() const {
    return m_moves;
}

int IntArray::getM_nbItems() const {
    return m_nbItems;
}
