#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(ChessBoard &b): board{b}, display{vector<vector<char>>(8, vector<char>(8, ' '))} {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display.at(i); 
        for (size_t j = 0; j < row.size(); ++j) {
            row.at(j) = (i+j) % 2 == 0 ? '_' : ' ';
        }
    }
}

void TextDisplay::notify(Tile t) {
    if (board.isOccupied(t)) {
        Piece p = board.getPiece(t);
        char ch;
        try { ch = getPieceChar(p); }
        catch (invalid_argument &r) {
            cerr << r.what() << endl;
            cerr << "called with tile " << t << endl;
            throw;
        }
        display.at(t.row).at(t.col) = ch;
    
    } else {
        display.at(t.row).at(t.col) = (t.row+t.col) % 2 == 0 ? '_' : ' ';
    }
}

// Note: the vector storing data begins at the bottom-left (a1 square)
// However, since we display from top to bottom, we have to use iterators differently.
void TextDisplay::print(ostream &out) const {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display.at(BOARD_ROWS-i-1); // notice this is not `i`
        
        cout << BOARD_ROWS-i << " "; // row number
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row.at(j);
        }
        cout << endl;
    }
    cout << "  abcdefgh";
}

void TextDisplay::printLarge(ostream &out) const {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display.at(BOARD_ROWS-i-1); // notice this is not `i`
        
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        cout << BOARD_ROWS-i; // row number
        for (size_t j = 0; j < row.size(); ++j) {
            cout << " | " << row.at(j);
        }
        cout << " | " << endl;
    }
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    cout << "    a   b   c   d   e   f   g   h";
}

std::ostream &operator<<(ostream &out, const TextDisplay &s) {
    s.printLarge(out);
    return out;
}
