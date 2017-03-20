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
    int& at(int index);
    int getAt(int index) const;


    int *getMoves() const;
    int length() const;

    IntArray& operator+=(IntArray const& a);

private:
    int m_moves[150];
    int m_length = 0;

};

IntArray operator+(IntArray const& a, IntArray const& b);


#endif //CHESS_INTARRAY_HPP
