#pragma once

#include "othutil.h"
#include "othello.h"

namespace oth {
    class Othello;

    /*
        Abstract class to contain all the functions to calculate the next move.
        Can be extended to make multiple classes that implements these function.
        The main Othello class will use these functions to calculate the moves.
    */
    class Engine {
private:

        friend class Othello;

public:

        // Returns the coordinates for color's best move.
        // Throws an error if no moves are possible.
        virtual Point nextMove(Othello& board) = 0;
    };
}