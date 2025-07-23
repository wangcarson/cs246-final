#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(ChessBoard &b): board{b}, display{vector<vector<char>>(8, vector<char>(8, ' '))} {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display[i]; 
        
        for (size_t j = 0; j < row.size(); ++j) {
            row[j] = (i+j) % 2 == 0 ? '_' : ' ';
        }
    }
}

void TextDisplay::notify(Tile t) {
    // cerr << "TextDisplay notified: Tile(" << t.row << ", " << t.col << ")" << endl; // debug

    if (board.isOccupied(t)) {
        Piece p = board.getPiece(t);
        char ch;
        try { ch = getPieceChar(p); }
        catch (invalid_argument &r) {
            cerr << r.what() << endl;
            cerr << "called with tile " << t << endl;
            throw;
        }
        display[t.row][t.col] = ch;
    
    } else {
        display[t.row][t.col] = (t.row+t.col) % 2 == 0 ? '_' : ' ';
    }
}

// Note: the vector storing data begins at the bottom-left (a1 square)
// However, since we display from top to bottom, we have to use iterators differently.
void TextDisplay::print(ostream &out) const {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display[BOARD_ROWS-i-1]; // notice this is not `i`
        
        cout << BOARD_ROWS-i << " "; // row number
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row[j];
        }
        cout << endl;
    }
    cout << "  abcdefgh" << endl;
}

std::ostream &operator<<(ostream &out, const TextDisplay &s) {
    s.print(out);
    return out;
}
