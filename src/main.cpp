#include "othello.h"
#include "randomengine.cpp"
#include "minimaxengine.cpp"
#include <stdlib.h>
#include <time.h>

int main() {
    // Initializes the board with the engines.

    srand(time(NULL));

    oth::MinimaxEngine en1 = oth::MinimaxEngine();
    oth::RandomEngine en2 = oth::RandomEngine();

    oth::Othello board(8, en2, en1);
    // board.drawBoard();

    board.startGame(oth::black);

    return 0;
}