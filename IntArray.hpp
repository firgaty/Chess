//
// Created by firgaty on 13/03/17.
//

#ifndef CHESS_INTARRAY_HPP
#define CHESS_INTARRAY_HPP


class IntArray {
public:
    IntArray()
    IntArray(int* array);

    bool add(int val);
    int at(int index);

    const int *getM_moves() const;
    int getM_nbItems() const;

private:
    int m_moves[150];
    int m_nbItems = 0;

};


#endif //CHESS_INTARRAY_HPP
