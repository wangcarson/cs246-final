#ifndef __TILE_H__
#define __TILE_H__
#include <iostream>
#include <stdexcept>

// board size constant.
const int BOARD_SIZE = 8;

// custom exceptions.
class tile_out_of_board: public std::out_of_range {
    public:
        tile_out_of_board(const std::string &s): out_of_range(s) {}
};

struct Tile {
    int row;
    int col;
    bool operator==(const Tile &other) const;
    Tile &operator+=(const Tile &other);
    Tile operator+(const Tile &other) const;
    bool inBoard() const;
};

// parsing helper function.
Tile parseTile(std::string s);

// output operator (for debugging).
std::ostream &operator<<(std::ostream &out, const Tile &t);

#endif
