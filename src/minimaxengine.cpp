#include "othengine.h"
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <limits>
#include <chrono>

#define RECURDEPTH 3
#define MAXSCORE int

namespace oth {
    class MinimaxEngine : public Engine {

private:
        
        // Struct to store the point combination combo.
        struct CoorPoint {
            Point coor;
            int score;
            
            CoorPoint() {coor = Point(); score = 0;}
            CoorPoint(Point coor, int score) : coor(coor) , score(score) {}
        };

        // Color of the tile that we would like to calculate for, and win
        Color winColor;
        int movesForeseen;
        Point chosenSquare;

        // Utility to do minimax
        // board: othello board reference
        // curDepth: the current depth of the recursion
        // isMaxing: whether the current step is maximizing or minimizing
        CoorPoint minimaxRecur(Othello& board, int curDepth, bool isMaxing) {

            // Switch the turn every time minimax is called.
            board.switchTurn();
            
            // When recursion have reached max depth
            if (curDepth == RECURDEPTH) {
                // Gets the coordinate for the current move
                Point point = board.undos.top().begin()->coor;

                // Score at the current step
                int score = board.getScore(winColor);

                // Don't forget to undo the move when returning something.
                board.undoMove();
                return CoorPoint(point, score);
            }

            // Choose the moves depending on the current color.
            const std::list<Point>* move;
            switch(board.turn) {
                case (white):
                    move = &board.whiteMove;
                    break;
                case (black):
                    move = &board.blackMove;
                    break;
            }

            // Create an array to contain all the CoorPoint values
            const int validMoves = move->size();
            CoorPoint* vals = new CoorPoint[validMoves];
            int valI = 0;

            // We need to copy the movelist
            std::list<Point> moveCopied;
            for (std::list<Point>::const_iterator it = move->begin(); it != move->end(); ++it)
                moveCopied.push_back(*it);

            // Iterate every of the current move
            for (std::list<Point>::const_iterator it = moveCopied.begin(); it != moveCopied.end(); ++it) {
                movesForeseen++;

                // Play the piece, as if playing self
                // Dont forget to enable undoing
                board.playPiece(board.turn, (*it).x, (*it).y, true);

                // Recur, depending when we want to maximize or minimize
                vals[valI++] = minimaxRecur(board, curDepth+1, !isMaxing);
            }

            CoorPoint minMaxValue;
            // Check if there is any valid moves
            if (validMoves > 0) {
                
                // Store pointer temporarily
                // Get the minimum / maximum depending on the state.
                CoorPoint* tempVal = isMaxing ? 
                    std::max_element(vals, vals+validMoves-1, [](CoorPoint a, CoorPoint b)  { return a.score < b.score; }) :
                    std::min_element(vals, vals+validMoves-1, [](CoorPoint a, CoorPoint b)  { return a.score < b.score; });

                // Decide on where to go
                if (curDepth == 0) {
                    // Do some pointer maths to get the list.
                    int index = tempVal - vals;

                    // Choose from value
                    std::list<Point>::const_iterator it = moveCopied.begin();
                    std::advance(it, index);

                    chosenSquare = *(it);
                }

                minMaxValue = *tempVal;

            } else {
                // If there is no valid moves,
                // Return min or max value.
                Point point = board.undos.top().begin()->coor;
                if (isMaxing) {
                    minMaxValue = CoorPoint(point, std::numeric_limits<MAXSCORE>::max());
                } else {
                    minMaxValue = CoorPoint(point, std::numeric_limits<MAXSCORE>::min());
                }
            }

            // Free the memory
            delete[] vals;

            // Don't forget to undo the move when returning something.
            board.undoMove();

            // Return
            return minMaxValue;
        }

public:

        Point nextMove(Othello& board) {

            movesForeseen = 0;

            // Set wincolor
            winColor = board.turn;

            // Switch turns, because in the function it will get switched again
            // To the original one
            board.switchTurn();

            // Measure time
            auto start = std::chrono::high_resolution_clock::now();

            // Gets the coordinate
            minimaxRecur(board, 0, true);

            // End time
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "[MINIMAX ENGINE] Number of moves foreseen: " << movesForeseen << " (Took: " << 
            std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms)" << std::endl;
            
            return chosenSquare;
        }
    };
}