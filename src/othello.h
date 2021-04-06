#pragma once

#include <list>
#include <stack>
#include "othutil.h"
#include "othengine.h"

namespace oth {
    // 8 Directions to iterate, when checking adjacent cells
    const static int direction[8][2] = {
        {1, 1},{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}
    };

    class Engine;

    /*
        Here, we define the othello board.
        Multiple othello boards can be made in this config
    */
    class Othello {

private:

    friend class Engine;

    // Describes what color a cell is occupying.
    // It also describes possible moves.
    struct Cell {
        // The piece color that occupies this cell.
        Color col;

        Cell();
    };

    // Struct for the undo stack.
    struct UndoData {
        Color col;
        Point coor;

        UndoData(Color col, Point coor);
    };

    // Scores
    int whiteScore;
    int blackScore;

    // Store engine objects.
    Engine* whiteEngine;
    Engine* blackEngine;

    // Helper variable to keep trach whether a tile is checked for potential moves.
    bool** _checked;

    // Matrix to store the current state of the board with the cells.
    Cell** board;

    // List to store all the active pieces' coordinates.
    std::list<Point> activePieces;


    // Makes everything in checked to be false.
    void _resetChecked();

    // Reset all the potential moves.
    void _resetPotentialMoves();

    // This function adds a new piece to the board, and do all the game calculations.
    // Returns whether the operation is successful.
    bool updatePiece(Color color, int x, int y);

    // Recalculates all possible moves, and puts it in an array.
    void updateValidMoves();

    // Checks if a tile can be placed in this position.
    void updatePotentialCell(int x, int y);

    // Walks the board to the specified direction. Will return the color
    // Of something that is different.
    Color walkBoard(int x, int y, const int* direction);

public:

    // Store potential moves
    std::list<Point> whiteMove;
    std::list<Point> blackMove;

    // Board size
    const int size;
    
    // Game pauses after "enter" is inputted.
    bool pauseEveryTurn = true;

    // Whose turn is it
    Color turn;

    // Stack to store the undos
    // The first index of the list is always the move that is played.
    std::stack<std::list<UndoData>> undos;
    
    // Initializes the othello board, with all the variables.
    Othello(int size, Engine& whiteEngine, Engine& blackEngine);

    // Deallocate mem
    ~Othello();

    // This function is to add a new piece to the board and nothing else.
    void playPiece(Color color, int x, int y, bool addUndoStack);

    // Gets the score of the specified color
    int getScore(Color color);

    // Undoes one move, and pops one from the stack.
    void undoMove();

    // Draws the board in the command line.
    void drawBoard();

    // Swaps the turn, and returns the current turn.
    Color switchTurn();

    // Starts the game, with turn being the first color to go.
    // pauseEveryTurn dictates whether the game needs "enter" input
    // Everytime a turn is over.
    void startGame(Color turn);

    };
}