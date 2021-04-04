#include "othengine.h"
#include <stdlib.h>
#include <list>

namespace oth {
    class RandomEngine : public Engine {

        Point nextMove(Othello& board) {
            
            // Get the valid moves for the color
            const std::list<Point>* move;
            switch(board.turn) {
                case (white):
                    move = &board.whiteMove;
                    break;
                case (black):
                    move = &board.blackMove;
                    break;
            }

            // Get the random position
            int n = rand() % move->size();

            // Advance pointer, and get the coords
            std::list<Point>::const_iterator it = move->begin();
            std::advance(it, n);

            return *it;
        }
    };
}