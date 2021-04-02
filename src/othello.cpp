#include "othello.h"
#include "othutil.h"
#include <iostream>
#include <list>

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

    addPiece(white, half-1, half-1);
    addPiece(black, half-1, half);
    addPiece(black, half, half-1);
    addPiece(white, half, half);
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

void Othello::addPiece(Color color, int x, int y) {
    // Make it return the point i think...
    // Don't insert if piece is already there
    if (board[y][x].col != none) return;

    // Add scores
    if (color == white) {
        whiteScore++;
    } else {
        blackScore++;
    }

    // Adds the corresponding piece to the board.
    board[y][x].col = color;

    // Adds the coordinate to the list.
    pieces.push_back(Point(x, y));

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
            if (!_checked[cy][cx] && (cx < size && cx > -1 && cy < size && cy > -1) && board[cy][cx].col == none) {

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
    y += direction[0]*2;
    x += direction[1]*2;

    // Walk the board, if the tile is not none, and still within the bounds.
    while (x < size && x > -1 && y < size && y > -1) {
        // Return the color, if different color is found.
        if (board[y][x].col != board[y-direction[0]][x-direction[1]].col) {
            return board[y][x].col;
        }

        // Walk the board
        y += direction[0];
        x += direction[1];        

    }
    return none;
}

void Othello::drawBoard() {

    // Iterate the board matrix
    for (int i = 0; i < size; i++) {
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