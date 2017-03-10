//
// Created by firgaty on 06/03/17.
//

#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class Board
 */
class Board {
public:
    Board();
    Board(int *plateau, unsigned int width, unsigned int height);

    void reset(int mode = 0);


    bool checkCase(int x, int y);
    bool isOccupied(unsigned int x, unsigned int y);
    bool isOpponent(unsigned int x, unsigned int y, int piece);
    void printBoard() const;

    // Different pieces moves:

    int* moves(unsigned int x, unsigned int y); // Gives all possible moves of a given piece at the coordinates (x,y) in a int[].
    int move(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2); // Moves piece from (x1,y1) to (x2,y2) and returns the piece that was at (x2,y2);
    int* movesKing(unsigned int x, unsigned int y);
    int* movesQueen(unsigned int x, unsigned int y);
    int* movesBishop(unsigned int x, unsigned int y);
    int* movesKnight(unsigned int x, unsigned int y);
    int* movesRook(unsigned int x, unsigned int y);
    int* movesPawn(unsigned int x, unsigned int y);

    // GETTERS AND SETTERS:
    int *getBoard();
    bool setBoard(int *board, unsigned int width = 8, unsigned int height = 8);
    int at(unsigned int x, unsigned int y); //returns the piece at (x,y).
    bool setAt(unsigned int x, unsigned int y, int piece); // returns true if the piece could be set.

    unsigned int getX(unsigned int pos);
    unsigned int getY(unsigned int pos);
    unsigned int getPos(unsigned int x, unsigned int y);


private:
    int m_board[64];
    unsigned int m_width;
    unsigned int m_height;

    int* reduceArray(int* array);

};



#endif //CHESS_BOARD_HPP
