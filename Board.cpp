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
 * @param x
 * @param y
 * @return a pointer to ant int[] that contains the positions in board of the different moves.
 */
int* Board::moves(unsigned int x, unsigned int y) {
    std::string str = (this->at(x, y) / 6 == 0) ? "White" : "black";
    int* moves;
    int count(0);

    switch(this->at(x, y) % 6) {
        case 0 : std::cout << str << " King :";
            moves = movesKing(x, y);
            break;
        case 1 : std::cout << str << " Queen :";
            moves = movesQueen(x, y);
            break;
        case 2 : std::cout << str << " Bishop :";
            moves = movesBishop(x, y);
            break;
        case 3 : std::cout << str << " Knight :";
            moves = movesKnight(x, y);
            break;
        case 4 : std::cout << str << " Rook :";
            moves = movesRook(x, y);
            break;
        case 5 : std::cout << str << " Pawn :";
            moves = movesPawn(x, y);
            break;
        default:
            moves = NULL;
            break;
    }

}

/**
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return the piece that was on the arriving case.
 */
int Board::move(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
    int out = this->at(x2, y2);
    setAt(x2, y2, at(x1, y1));
    setAt(x1, y1, -1);
    return out;
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



/**
 * @param x
 * @param y
 * @return true if case in board.
 */
bool Board::checkCase(int x, int y) {
    return x >= 0 && x < this->m_width && y >= 0 && y < this->m_height;
}
/**
 * @param x
 * @param y
 * @return true if the case is occupied (int[x + m_width  *y] >= 0)
 */
bool Board::isOccupied(unsigned int x, unsigned int y) {
    return this->at(x, y) >= 0;
}
/**
 * @param x
 * @param y
 * @param piece
 * @return true if the piece at(x, y) is of different color than piece
 */
bool Board::isOpponent(unsigned int x, unsigned int y, int piece) {
    return (this->at(x, y) / 2) != (piece / 2);
}

/**
 *  Prints the Board in the terminal.
 */
void Board::printBoard() const {
    for(int j(0); j < this->m_height; j++) {
        for(int i(0); i < this->m_width; i++) {
            std::cout << this->m_board[i + j * 8] << ", ";
        }
        std::cout << std::endl;
    }
}
/**
 *
 * @return int[] the board
 */
int* Board::getBoard() {
    this->printBoard();
    return this->m_board;
}
/**
 * @param board
 * @param width
 * @param height
 * @return true if board could be set.
 */
bool Board::setBoard(int *board, unsigned int width, unsigned int height) {
    for(int i(0); i < width*height; i++ ) {
        this->m_board[i] = board[i];
    }
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

unsigned  int Board::getX(unsigned int pos) {
    return pos % m_width;
}

unsigned int Board::getY(unsigned int pos) {
    return pos / m_width;
}

unsigned int Board::getPos(unsigned int x, unsigned int y) {
    return x + y * m_width;
}