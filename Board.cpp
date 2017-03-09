//
// Created by firgaty on 06/03/17.
//

#include "Board.hpp"

Board::Board() {
    int pieces[] =
            {
                    10,  9,  8,  7,  6,  8,  9, 10,
                    11, 11, 11, 11, 11, 11, 11, 11,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                     5,  5,  5,  5,  5,  5,  5,  5,
                     4,  3,  2,  1,  0,  2,  3,  4,
            };
    this->setBoard(pieces, 8, 8);

}

/**
 * @param board
 * @param width
 * @param height
 * @return
 */
bool Board::setBoard(int *board, unsigned int width, unsigned int height) {
    this->m_board = board;
    this->m_width = width;
    this->m_height = height;
    return true;
}

/**
 * @param x
 * @param y
 * @return piece at (x,y)
 */
int Board::at(unsigned int x, unsigned int y) {
    if(!this->checkCase(x, y)) return -1;
    return this->m_board[x + y * this->m_width];
}
/**
 * @param x
 * @param y
 * @param piece
 * @return true if case could be set.
 */
bool Board::setAt(unsigned int x, unsigned int y, int piece) {
    if(!this->checkCase(x, y)) return false;
    int out(this->m_board[x + y * this->m_width]);
    this->m_board[x + y * this->m_width] = piece;
    return true;
}
/**
 * @param x
 * @param y
 * @return true if case in board.
 */
bool Board::checkCase(unsigned int x, unsigned int y) {
    return x >= 0 && x < this->m_width && y >= 0 && y < this->m_height;
}

/**
 * @param mode
 */
void Board::reset(int mode) {
    switch (mode) {
        case 0 :
            int pieces[] =
                    {
                            10,  9,  8,  7,  6,  8,  9, 10,
                            11, 11, 11, 11, 11, 11, 11, 11,
                            -1, -1, -1, -1, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1, -1, -1, -1,
                             5,  5,  5,  5,  5,  5,  5,  5,
                             4,  3,  2,  1,  0,  2,  3,  4,
                    };
            this->setBoard(pieces, 8, 8);
            break;
    }
}

int* Board::getBoard() {
    return this->m_board;
}


