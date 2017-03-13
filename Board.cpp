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
        case 1 : // Test moves.
            int tpieces[] =
                    {
                            -1, -1, -1, -1, -1, -1, -1, -1,
                            -1,  4, -1, -1, -1, -1, -1, -1,
                            -1, -1, -1,  3, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1, -1,  1, -1,
                            -1, -1, -1, -1, -1, -1,  6, -1,
                            -1,  0, -1, -1,  2,  5, -1, -1,
                            -1, -1, -1,  5, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1, -1, -1, -1,
                    };
            this->setBoard(tpieces, 8, 8);
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
            this->printMoves(moves);
            break;
        default:
            std::cout << "NONE :" << this->at(x, y) % 6;
            int out[] = {-1};
            moves = out;
            break;
    }
    std::cout << "\n" << std::endl;

    // Now we reduce the array to the minimum;
    // We suppose every position to be different;
    // last element of array is -1;
    moves = this->reduceArray(moves);
    this->printMoves(moves);
    return moves;
}

/**
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
 * @param x
 * @param y
 * @return the moves of the king on (x,y)
 */
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
/**
 * @param x
 * @param y
 * @return the moves of the Queen on (x,y)
 */
int* Board::movesQueen(unsigned int x, unsigned int y) {
    int* diagonal = this->movesBishop(x, y);
    int* line = this->movesRook(x, y);

    return this->concArrays(diagonal, line);
}
/**
 * @param x
 * @param y
 * @return the moves of the bishop on (x,y)
 */
int* Board::movesBishop(unsigned int x, unsigned int y) {
    int* dr = this->diagonalMoves(x, y, true, true);
    int* dl = this->diagonalMoves(x, y, true, false);
    int* ur = this->diagonalMoves(x, y, false, true);
    int* ul = this->diagonalMoves(x, y, false, false);

    return this->concArrays(dr, this->concArrays(dl, this->concArrays(ur, ul)));
}
/**
 * @param x
 * @param y
 * @return the moves of the knight on (x,y)
 */
int* Board::movesKnight(unsigned int x, unsigned int y) {
    int possibleMoves[] = {
             1,  2,
             1, -2,
             2,  1,
             2, -1,
            -1,  2,
            -1, -2,
            -2,  1,
            -2, -1,
    };

    int moves[10];
    int count(0);

    for(int i(0); i < 16; i+=2) {
        if(this->isInBoard(x + possibleMoves[i], y + possibleMoves[i + 2]))
            if(!this->isOccupied(x + possibleMoves[i], y + possibleMoves[i + 2])
               || this->isOpponent(x + possibleMoves[i], y + possibleMoves[i + 2], this->at(x, y))) {
                moves[count] = getPos(x + possibleMoves[i], y + possibleMoves[i + 2]);
                count++;
            }
    }
    moves[count] = -1;
    int* out = moves;
    return out;

}
/**
 * @param x
 * @param y
 * @return the moves of the rook on (x,y)
 */
int* Board::movesRook(unsigned int x, unsigned int y) {
    int* l = this->lineMoves(x, y, 0);
    int* d = this->lineMoves(x, y, 1);
    int* r = this->lineMoves(x, y, 2);
    int* u = this->lineMoves(x, y, 3);

    return this->concArrays(l, this->concArrays(d, this->concArrays(r, u)));
}
/**
 * @param x
 * @param y
 * @return the moves of the pawn on (x,y)
 */
int* Board::movesPawn(unsigned int x, unsigned int y) {
    int moves[5];
    int direction = (at(x, y) / 6 == 0) ? -1 : 1; // -1 : White, 1: Black. Sets direction.
    int count(0);

    //Test if there are any piece on each sides:
    if(at(x - 1, y + direction) >= 0) {
        moves[count] = getPos(x - 1, y + direction);
        count++;
    }
    if(at(x + 1, y + direction) >= 0) {
        moves[count] = getPos(x - 1, y + direction);
        count++;
    }
    if(!at(x, y + direction) >= 0) {
        moves[count] = getPos(x, y + direction);
        count ++;

        // Test if first move, if so : can advance 2 cases if no one 2 cases front.
        if((direction == -1 && x == 6 || direction == 1 && x == 1) && at(x, y + 2 * direction) == -1) {
            moves[count] = getPos(x, y + 2 * direction);
            count++;
        }
    }

    moves[count] = -1;

    int* out = moves;
    return out;
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
/**
 * @param array1
 * @param array2
 * @return returns the concatenation of reduced array1 + array2.
 */
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
/**
 * @param moves
 * Print the list of moves.
 */
void Board::printMoves(int *moves) {
    std::cout << "Moves :" << std::endl;
    int i(0);
    while(moves[i] >= 0) {
        std::cout << this->getX((unsigned int) moves[i])
                  << ", "
                  << this->getY((unsigned int) moves[i])
                  << std::endl;
    }
}