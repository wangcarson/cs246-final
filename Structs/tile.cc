#include "tile.h"

// Tile methods.
bool Tile::operator==(const Tile &other) const {
    return row == other.row && col == other.col;
}
Tile &Tile::operator+=(const Tile &other) {
    row += other.row;
    col += other.col;
    return *this;
}
Tile Tile::operator+(const Tile &other) const {
    Tile tmp{*this};
    return tmp += other;
}
bool Tile::inBoard() const {
    return col >= 0 && row >= 0 && col < BOARD_SIZE && row < BOARD_SIZE; 
}

// Helper functions
Tile parseTile(std::string s) {
    if (s.size() != 2 || s[0] < 'a' || s[0] > 'h' || s[1] < '1' || s[1] > '8') {
        throw std::invalid_argument("parseTile(): Invalid tile " + s);
    }
    int col = s[0] - 'a'; // 'a' is 0
    int row = s[1] - '1'; // '1' is 0
    return Tile{row, col};
}

std::ostream &operator<<(std::ostream &out, const Tile &t) {
    out << static_cast<char>('a' + t.col) << (t.row + 1);
    return out;
}
