#include "othello.h"
#include "randomengine.cpp"
#include "minimaxengine.cpp"
#include "inputengine.cpp"
#include <stdlib.h>
#include <time.h>

int main() {
    // Initializes the board with the engines.

    srand(time(NULL)); // TODO: Change this

    std::cout << "Welcome to othello! The white piece will be \n";
    std::cout << "played by a random engine, while the black piece will be \n";
    std::cout << "played by minimax algorithm with 3 recursion depths.\n" << std::endl;

    oth::MinimaxEngine en1 = oth::MinimaxEngine();
    oth::InputEngine en2 = oth::InputEngine();

    oth::Othello board(8, en2, en1);
    // board.pauseEveryTurn = false;

    board.startGame(oth::black);

    return 0;
}