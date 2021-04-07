#include "othengine.h"
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <limits>
#include <chrono>

#define RECURDEPTH 4
#define SCORE int

namespace oth {
    class MinimaxEngine : public Engine {

private:
        
        // Color of the tile that we would like to calculate for, and win
        Color winColor;
        int movesForeseen;
        Point chosenSquare;

        // Store board reference
        Othello* board;


        // Utility to do minimax
        // curDepth: the current depth of the recursion
        // isMaxing: whether the current step is maximizing or minimizing
        SCORE minimaxRecur(int curDepth, bool isMaxing) {
            movesForeseen++;

            // Switch the turn every time minimax is called.
            board->switchTurn();
            
            // When recursion have reached max depth
            if (curDepth == RECURDEPTH) {
                // Score at the current step
                int score = board->getScore(winColor);

                // Don't forget to undo the move when returning something.
                board->undoMove();
                return score;
            }

            // Choose the moves depending on the current color.
            std::list<Point> move;
            switch(board->turn) {
                case (white):
                    move = board->whiteMove;
                    break;
                case (black):
                    move = board->blackMove;
                    break;
            }

            // Create an array to contain all the score values
            const int validMoves = move.size();
            SCORE* vals = new SCORE[validMoves];
            int valI = 0;

            // Iterate every of the current move
            for (std::list<Point>::const_iterator it = move.begin(); it != move.end(); ++it) {
                // Play the piece, as if playing self
                // Dont forget to enable undoing
                board->playPiece(board->turn, (*it).x, (*it).y, true);

                // Recur, depending when we want to maximize or minimize
                vals[valI++] = minimaxRecur(curDepth+1, !isMaxing);
            }

            SCORE minMaxValue;
            // Check if there is any valid moves
            if (validMoves > 0) {
                
                // Store pointer temporarily
                // Get the minimum / maximum depending on the state.
                SCORE* tempVal = isMaxing ? 
                    std::max_element(vals, vals+validMoves-1):
                    std::min_element(vals, vals+validMoves-1);

                // Decide on where to go
                if (curDepth == 0) {

                    // Choose from value
                    std::list<Point>::const_iterator it = move.begin();
                    // Do some pointer maths to get the list.
                    std::advance(it, tempVal - vals);
                    chosenSquare = *(it);
                }
                // Assign
                minMaxValue = *tempVal;

            } else {
                // If there is no valid moves,
                // Return min or max value.
                minMaxValue = isMaxing ?
                    std::numeric_limits<SCORE>::max():
                    std::numeric_limits<SCORE>::min();
            }

            // Free the memory
            delete[] vals;

            // Don't forget to undo the move when returning something.
            board->undoMove();

            // Return
            return minMaxValue;
        }

public:

        Point nextMove(Othello& board) {
            
            // Init
            movesForeseen = 0;

            // Set board reference
            this->board = &board;

            // Set wincolor
            winColor = board.turn;

            // Switch turns, because in the function it will get switched again
            // To the original one
            board.switchTurn();

            // Measure time
            auto start = std::chrono::high_resolution_clock::now();

            // Gets the coordinate
            minimaxRecur(0, true);

            // End time
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "[MINIMAX ENGINE] Number of moves foreseen: " << movesForeseen << " (Took: " << 
            std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms)" << std::endl;
            
            return chosenSquare;
        }
    };
}