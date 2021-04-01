#pragma once
#include <list>
#include <iterator>

namespace oth {

    /*
        Color of the othello pieces. For now, it's
        only black and white.
    */
    enum Color : unsigned char {
        none,
        black,
        white
    };

    // 8 Directions too iterate, when checking adjacent cells
    const static int direction[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};

    /*
        Here, we define the othello board.
        Multiple othello boards can be made in this config
    */
    class Othello {

private:

    // Describes what color a cell is occupying.
    // It also describes possible moves.
    struct Cell {
        // The piece color that occupies this cell.
        Color col;

        Cell();
    };

    // Simple struct to store coordinate.
    struct Point {
        int x;
        int y;

        Point(int x, int y);
    };

    // Scores
    int whiteScore;
    int blackScore;

    // Helper variable to store whether a tile is checked.
    bool** _checked;

    // Matrix to store the current state of the board with the cells.
    Cell** board;

    // List to store all the active pieces' coordinates.
    std::list<Point> pieces;

    // Store potential moves
    std::list<Point> whiteMove;
    std::list<Point> blackMove;

    // Makes everything in checked to be false.
    void _resetChecked();

    // Reset all the potential moves.
    void _resetPotentialMoves();

    // This function is to add a new piece to the board.
    // TODO: It will get added to the active list or something...
    void addPiece(Color color, int x, int y);

    // Recalculates all possible moves, and puts it in an array.
    void updateValidMoves();

    // Checks if a tile can be placed in this position.
    void updatePotentialCell(int x, int y);

    // Walks the board to the specified direction. Will return the color
    // Of something that is different.
    Color walkBoard(int x, int y, const int* direction);

public:
    // Board size
    const int size;
    
    // Initializes the othello board, with all the variables.
    Othello(int size);

    // Deallocate mem
    ~Othello();

    // Draws the board in the command line.
    void drawBoard();

    };

}