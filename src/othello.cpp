#include "othello.h"
#include <iostream>

using namespace oth;

Othello::Piece::Piece() {
    this->col = none;
}

Othello::Othello(int size) : size(size) {

    // Create the first dimension
    this->board = new Othello::Piece*[size];

    // Create the second dimension
    for (int i = 0; i < size; i++) {
        this->board[i] = new Othello::Piece[size];
    }
}

Othello::~Othello() {
    // Deallocate everything
    // First, deallocate the extra dimension
    for (int i = 0; i < this->size; i++) {
        delete[] this->board[i];
    }

    delete[] this->board;
}

void Othello::drawBoard() {
    const int size = this->size;
    Othello::Piece** board = this->board;

    // Iterate the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            // Print corresponding symbol
            char symbol;

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
}