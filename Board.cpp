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
bool Board::isInBoard(int x, int y) {
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
 * @param x
 * @param y
 * @return a pointer to ant int[] that contains the positions in board of the different moves.
 */
int* Board::moves(unsigned int x, unsigned int y) {
    std::string str = (this->at(x, y) / 6 == 0) ? "White" : "black";
    int *moves;

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
            int out[] = {-1};
            moves = out;
            break;
    }

    // Now we reduce the array to the minimum;
    // We suppose every position to be different;
    // last element of array is -1;
    int* out = this->reduceArray(moves);
    return out;
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

int* Board::movesKing(unsigned int x, unsigned int y) {
    int pos[20];
    int count(0);
    for(int j(y - 1); j <= (y + 1); j++) {
        for(int i(x - 1); i <= (x + 1); i++) {
            if(this->isInBoard(x, y))
                if(!this->isOccupied((unsigned int) i, (unsigned int) j) || this->isOpponent((unsigned int) i, (unsigned int) j, this->at(x, y))) {
                    pos[count] = getPos(x, y);
                    count++;
                }
        }
    }
    pos[count] = -1;
    int* out = pos;
    return out;
}
int* Board::movesQueen(unsigned int x, unsigned int y) {
}
int* Board::movesBishop(unsigned int x, unsigned int y) {
    int* dr = this->diagonalMoves(x, y, true, true);
    int* dl = this->diagonalMoves(x, y, true, false);
    int* ur = this->diagonalMoves(x, y, false, true);
    int* ul = this->diagonalMoves(x, y, false, false);

    return this->concArrays(dr, this->concArrays(dl, this->concArrays(ur, ul)));
}

int* Board::movesKnight(unsigned int x, unsigned int y) {}
int* Board::movesRook(unsigned int x, unsigned int y) {}
int* Board::movesPawn(unsigned int x, unsigned int y) {}
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
    for(int i(0); i < width * height; i++ ) {
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
    if(!this->isInBoard(x, y)) return -1;
    return this->m_board[x + y * this->m_width];
}

/**
 * @param x
 * @param y
 * @param piece
 * @return true if case could be set.
 */
bool Board::setAt(unsigned int x, unsigned int y, int piece) {
    if(!this->isInBoard(x, y)) return false;
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


// PRIVATE

int* Board::reduceArray(int* array) {
    int i(0);
    while(array[i] >= 0) {
        i++;
    }
    int foo[i + 1];
    for(int j(0); j < i; j++) {
        foo[j] = array[j];
    }
    foo[i] = -1;
    int* out = foo;
    return out;
}

int Board::arrayLength(int *array) {
    int i(0);
    while(array[i] >= 0) {
        i++;
    }

    return i;
}

int* Board::diagonalMoves(unsigned int x, unsigned int y, bool down, bool right) {
    int moves[100];
    int d = (down) ? 1 : -1;
    int r = (right) ? 1 : -1;

    int i(1);
    while(this->isInBoard((int) (x) + i * r, (int) (y) + i * d) &&
            (!this->isOccupied(x + i * r, y + i * d) || this->isOpponent(x + i * r, y + i * d, this->at(x, y)))) {
        moves[i - 1] = this->getPos(x + i * r, y + i * d);
        i++;
        if(this->isOpponent(x + i * r, y + i * d, this->at(x, y))) break;
    }
    moves[i - 1] = -1;
    int* out = moves;
    return out;
}
/**
 *
 * @param x
 * @param y
 * @param mode 0 : left, 1: down, 2 : right, 3 : up.
 * @return
 */
int* Board::lineMoves(unsigned int x, unsigned int y, int mode) {
    int xop;
    int yop;
    int i(1);
    int moves[100];

    switch (mode) {
        case 0:
            xop = -1;
            yop = 0;
            break;
        case 1:
            xop = 0;
            yop = 1;
            break;
        case 2:
            xop = 1;
            yop = 0;
            break;
        case 3:
            xop = 0;
            yop = -1;
           break;
        default:
            xop = 1;
            yop = 1;
    }

    while(this->isInBoard((int) (x) + i * xop, (int) (y) + i * yop) &&
          (!this->isOccupied(x + i * xop, y + i * yop) || this->isOpponent(x + i * xop, y + i * yop, this->at(x, y)))) {
        moves[i - 1] = this->getPos(x + i * xop, y + i * yop);
        i++;
        if(this->isOpponent(x + i * xop, y + i * yop, this->at(x, y))) break;
    }
    moves[i - 1] = -1;
    int* out = moves;
    return out;

}

int* Board::concArrays(int *array1, int *array2) {
    array1 = reduceArray(array1);
    array2 = reduceArray(array2);
    int array[this->arrayLength(array1) + this->arrayLength(array2)];

    for (int i(0); i < this->arrayLength(array1); i++) {
        array[i] = array1[i];
    }
    for(int i(this->arrayLength(array1)); i <= this->arrayLength(array2); i++ ) {
        array[i] = array2[i];
    }

    int* out = array;
    return out;
}
