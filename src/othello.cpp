#include "othello.h"
#include "othutil.h"
#include <iostream>
#include <list>
#include <limits>

using namespace oth;

Othello::Cell::Cell() {
    this->col = none;
}

Point::Point(int x, int y) : x(x), y(y) {}

Othello::Othello(int size, const Engine& whiteEngine, const Engine& blackEngine) :
    size(size),
    whiteEngine(&whiteEngine),
    blackEngine(&blackEngine)
    {

    // Create the first dimension
    this->board = new Cell*[size];
    this->_checked = new bool*[size];

    // Create the second dimension
    for (int i = 0; i < size; i++) {
        this->board[i] = new Cell[size];
        this->_checked[i] = new bool[size];
    }

    // Fill the middle of the board with the initial pieces.
    int half = size/2;

    // Add default pieces
    addPiece(white, half-1, half-1);
    addPiece(black, half-1, half);
    addPiece(black, half, half-1);
    addPiece(white, half, half);

    // And update valid moves
    updateValidMoves();
}

Othello::~Othello() {
    // Deallocate everything
    // First, deallocate the extra dimension
    for (int i = 0; i < size; i++) {
        delete[] this->board[i];
        delete[] this->_checked[i];
    }

    delete[] this->board;
    delete[] this->_checked;
}


void Othello::_resetChecked() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            _checked[i][j] = false;
        }
    }
}

void Othello::_resetPotentialMoves() {
    whiteMove.clear();
    blackMove.clear();
}

bool Othello::addPiece(Color color, int x, int y) {
    if (!(x > -1 && y > -1 && x < size && y < size) || board[y][x].col != none) return false;

    // Add scores
    if (color == white) {
        whiteScore++;
    } else {
        blackScore++;
    }

    // Adds the corresponding piece to the board.
    board[y][x].col = color;

    // Adds the coordinate of the piece to the list.
    pieces.push_back(Point(x, y));

    return true;
}

void Othello::playPiece(Color color, int x, int y) {

    // Adds the pice
    addPiece(color, x, y);

    // Walk the board, to see any takes.
    for (int i = 0; i < 8; i++) {
        Color edgeColor = walkBoard(x, y, direction[i]);
        
        if (edgeColor != none && color == edgeColor) {
            while(true) {
                y += direction[i][0];
                x += direction[i][1];

                if (board[y][x].col == edgeColor) break;

                // Add and minus score
                if (color == white) {
                    whiteScore++;
                    blackScore--;
                } else {
                    blackScore++;
                    whiteScore--;
                }

                board[y][x].col = color;
            }
        }
    }

    updateValidMoves();
}

void Othello::updateValidMoves() {
    // Reconstructs the possibilities.
    _resetChecked();
    _resetPotentialMoves();

    // Iterates the present pieces
    for (std::list<Point>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
        int x = it->x;
        int y = it->y;

        // Iterate all the directions adjacent to current tile.
        for (int i = 0; i < 8; i++) {

            const int* dir = direction[i];
            int cy = y + dir[0];
            int cx = x + dir[1];

            // If this cell is not checked yet and not occupied, do stuff
            // Also check if the cell is still inside the boundary
            if ((cx < size && cx > -1 && cy < size && cy > -1) && board[cy][cx].col == none && !_checked[cy][cx]) {

                // Tag as checked
                _checked[cy][cx] = true;

                // Check if the move is valid.
                updatePotentialCell(cx, cy);
            }
        }
    }
}

void Othello::updatePotentialCell(int x, int y) {
    // Iterate all the directions adjacent to current tile.
    for (int i = 0; i < 8; i++) {
        switch (walkBoard(x, y, direction[i])) {
            case white:
                whiteMove.push_back(Point(x, y));
                break;
            case black:
                blackMove.push_back(Point(x, y));
                break;
        }
    }
}

Color Othello::walkBoard(int x, int y, const int* direction) {
    y += direction[0];
    x += direction[1];

    // If out of bounds or no color, continue.
    if (!(x < this->size && x > -1 && y < this->size && y > -1)) return none;
    if (board[y][x].col == none) return none;

    // Eat color is the color of piece that will be consumed if the move is valid
    Color eatColor = board[y][x].col;

    // Walk the board, if the tile is not none, and still within the bounds.
    do {
        // Return the color, if different color is found.
        if (board[y][x].col != eatColor) {
            return board[y][x].col;
        }

        // Walk
        y += direction[0];
        x += direction[1];        

    } while (x < this->size && x > -1 && y < this->size && y > -1);
    return none;
}

void Othello::drawBoard() {

    // Print first row of number coords
    std::cout << "  ";
    for (int i = 0; i < size;) std::cout << (++i) % 10 << " ";
    std::cout << std::endl;

    // Iterate the board matrix
    for (int i = 0; i < size; i++) {
        // Print column number coords
        std::cout << (i+1) % 10 << " ";

        for (int j = 0; j < size; j++) {

            // Print corresponding symbol
            char symbol;

            // Print the piece, if the cell is occupied.
            switch(board[i][j].col) {
                case(black):
                    symbol = 'O';
                    break;
                case(white):
                    symbol = 'X';
                    break;
                default:
                    symbol = '_';
            }

            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "White: " << whiteScore << " | Black: " << blackScore << std::endl;
}

void Othello::startGame(Color turn) {
    // Start the game, and loop until complete.

    drawBoard();

    // While there is still valid moves, we loop.
    while (whiteMove.size() > 0 && blackMove.size() > 0) {

        if (pauseEveryTurn) {
            std::cout << "Press Enter to Continue";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }

        std::cout << (turn == white ? "White" : "Black") << "'s Turn" << std::endl;

        // Assign the correct engine
        const Engine* curEngine;
        switch (turn) {
            case(black):
                curEngine = blackEngine;
                break;
            case(white):
                curEngine = whiteEngine;
                break;
        }

        // Run the engine
        Point move = curEngine->nextMove(*this, turn);

        // And insert the move.
        std::cout << (turn == white ? "White" : "Black") << " Plays (" << move.x+1 << ", " << move.y+1 << ")" << std::endl;
        playPiece(turn, move.x, move.y);

        drawBoard();
        
        // Switch the turns
        turn = turn == white ? black : white;
    }

    std::cout << "Game over" << std::endl;
}