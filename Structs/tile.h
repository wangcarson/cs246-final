
// board size constants.
const int BOARD_SIZE = 8;

class tile_out_of_board: public std::out_of_range {
    public:
        tile_out_of_board(const std::string &s): out_of_range(s) {}
};

struct Tile {
    int row;
    int col;
    bool operator==(const Tile &other) const {
        return row == other.row && col == other.col;
    }
    Tile &operator+=(const Tile &other) {
        row += other.row;
    	col += other.col;
    	return *this;
    }
    Tile operator+(const Tile &other) const {
        Tile tmp{*this};
        return tmp += other;
    }
    bool inBoard() const {
        return col >= 0 && row >= 0 && col < BOARD_SIZE && row < BOARD_SIZE; 
    }
};

// Parsing and output.
Tile parseTile(std::string s);
std::ostream &operator<<(std::ostream &out, const Tile &t);
