#pragma once
#include <iostream>

namespace oth {

    /*
        Color of the othello pieces. For now, it's
        only black and white.
    */
    enum Color : unsigned char {
        none,
        black,
        white
    };


    /*
        Here, we define the othello board.
        Multiple othello boards can be made in this config
    */
    class Othello {

private:

    // Describes what color a cell is occupying.
    // It also describes possible moves.
    struct Cell {
        // Whether the cell is occupied by a piece, or is a possible move.
        bool occupied;

        // The piece color that (possibly) occupies this cell.
        Color col;

        Cell();
    };

    // Matrix to store the pieces data.
    Cell** board;

    // This function is to add a new piece to the board.
    // TODO: It will get added to the active list or something...
    void addPiece(Color color, int x, int y);

public:
    // Board size
    const int size;
    
    // Initializes the othello board, with all the variables.
    Othello(int size);

    // Deallocate mem
    ~Othello();

    // Draws the board in the command line.
    void drawBoard();

    };

}