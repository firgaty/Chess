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

    int* moves(unsigned int x, unsigned int y); // Gives all possible moves of a given piece at the coordinates (x,y) in a int[].
    int move(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2); // Moves piece from (x1,y1) to (x2,y2) and returns the piece that was at (x2,y2);
    void reset(int mode = 0);


    bool checkCase(unsigned int x, unsigned int y);

    // GETTERS AND SETTERS:
    int *getBoard();
    int at(unsigned int x, unsigned int y); //returns the piece at (x,y).
    bool setAt(unsigned int x, unsigned int y, int piece); // returns true if the piece could be set.
    bool setBoard(int *board, unsigned int width = 8, unsigned int height = 8);



private:
    int *m_board;
    unsigned int m_width;
    unsigned int m_height;

};



#endif //CHESS_BOARD_HPP
