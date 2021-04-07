#include "othengine.h"
#include <list>
#include <iostream>
#include <string>
#include <regex>

namespace oth {
    class InputEngine : public Engine {

        static bool is_number(const std::string& s) {
            std::string::const_iterator it = s.begin();
            while (it != s.end() && std::isdigit(*it)) ++it;
            return !s.empty() && it == s.end();
        }

        Point nextMove(Othello& board) {
            
            // Regex
            std::regex rcoor("^\\s*(\\d*),\\s*(\\d*)");
            
            
            do {
                
                std::string input;
                std::smatch rmatch;

                // Print input instruction
                std::cout << "Input your move (Ex. `5,3`): ";
                std::cin >> input;

                // Regex to get the coords
                std::regex_search(input, rmatch, rcoor);

                // Check if the args can be casted to int, and has sufficient arg
                if (rmatch.size() >= 3 && is_number(rmatch[1]) && is_number(rmatch[2])) {
                    // Casts
                    int x = std::stoi(rmatch[1]) - 1;
                    int y = std::stoi(rmatch[2]) - 1;

                    // Get the valid moves for the color
                    std::list<Point>* move;
                    switch(board.turn) {
                        case (white):
                            move = &board.whiteMove;
                            break;
                        case (black):
                            move = &board.blackMove;
                            break;
                    }

                    // Check if the input is in the possible moves
                    if (std::any_of(move->begin(), move->end(), [x, y](Point& p) { return (p.x == x && p.y == y); })) {
                        return Point(x, y);
                    }
                }

                std::cout << "Wrong input" << std::endl;
            } while (true);
        }
    };
}