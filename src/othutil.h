#pragma once

namespace oth {
    // Simple struct to store coordinate.
    struct Point {
        int x;
        int y;

        Point(int x, int y);
    };

    /*
        Color of the othello pieces. For now, it's
        only black and white.
    */
    enum Color : unsigned char {
        none,
        black,
        white
    };
}