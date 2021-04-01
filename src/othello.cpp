#include "othello.h"
#include <iostream>

using namespace oth;

Othello::Cell::Cell() {
    this->occupied = false;
    this->col = none;
}

Othello::Othello(int size) : size(size) {

    // Create the first dimension
    this->board = new Cell*[size];

    // Create the second dimension
    for (int i = 0; i < size; i++) {
        this->board[i] = new Cell[size];
    }

    // Fill the middle of the board with the initial pieces.
    Cell** board = this->board;
    int half = size/2;

    addPiece(black, half-1, half-1);
    addPiece(white, half-1, half);
    addPiece(white, half, half-1);
    addPiece(black, half, half);
}

Othello::~Othello() {
    // Deallocate everything
    // First, deallocate the extra dimension
    for (int i = 0; i < this->size; i++) {
        delete[] this->board[i];
    }

    delete[] this->board;
}


void Othello::addPiece(Color color, int x, int y) {
    // Adds the corresponding piece to the board.
    Cell* curCell = &board[y][x];

    curCell->col = color;
    curCell->occupied = true;
}

void Othello::drawBoard() {
    const int size = this->size;
    Cell** board = this->board;

    // Iterate the board matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            Cell* curCell = &board[i][j];

            // Print corresponding symbol
            char symbol;

            // Print the piece, if the cell is occupied.
            if (curCell->occupied) {
                switch(curCell->col) {
                    case(black):
                        symbol = 'O';
                        break;
                    case(white):
                        symbol = 'X';
                        break;
                    default:
                        symbol = '_';
                }
            } else {
                symbol = '_';
            }

            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }
}