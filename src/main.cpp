#include "othello.h"
#include "randomengine.cpp"

int main() {
    // Initializes the board with the engines.
    oth::Othello board(8, oth::RandomEngine(), oth::RandomEngine());

    board.drawBoard();

    return 0;
}