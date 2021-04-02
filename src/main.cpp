#include "othello.h"
#include "randomengine.cpp"
#include <stdlib.h>
#include <time.h>

int main() {
    // Initializes the board with the engines.

    srand(time(NULL));

    oth::Othello board(16, oth::RandomEngine(), oth::RandomEngine());
    // board.drawBoard();

    board.startGame(oth::black);

    return 0;
}