#include "othengine.h"

namespace oth {
    class RandomEngine : public Engine {

        Point nextMove(const Othello& board, Color color) const {
            return Point(0, 0);
        }
    };
}