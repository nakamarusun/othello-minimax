#pragma once

#include "othutil.h"

namespace oth {
    class Othello;
    class Engine {
        /*
            Abstract class to contain all the functions to calculate the next move.
            Can be extended to make multiple classes that implements these function.
            The main Othello class will use these functions to calculate the moves.
        */

        virtual Point nextMove(Othello& board, Color color) = 0;
    };
}