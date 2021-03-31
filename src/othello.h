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
    struct Piece {
        Color col;

        Piece();
    };

    // Matrix to store the pieces data.
    Piece** board;

public:
    // Board size
    const int size;
    
    // Initializes the othello board, with all the variables.
    Othello(int size);

    // Deallocate
    ~Othello();

    void drawBoard();

    };

}