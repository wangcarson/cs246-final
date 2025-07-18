#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(BoardManager bm): 
boardManager{bm}, display{vector<vector<char>>(8, vector<char>(8, ' '))} {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display[i]; 
        
        for (size_t j = 0; j < row.size(); ++j) {
            row[j] = (i+j) % 2 == 0 ? ' ' : '_';
        }
    }
}

void TextDisplay::notify(Tile t) {
    display[t.row][t.col] = PIECE_CHAR_MAP.at(boardManager.getBoard().getPiece(t));
}

// Note: the vector storing data begins at the bottom-left (a1 square)
// However, since we display from top to bottom, we have to use iterators differently.
void TextDisplay::print(ostream &out) const {
    for (size_t i = 0; i < display.size(); ++i) {
        auto &row = display[display.size()-i]; // notice this is not `i` 
        
        cout << i << " "; // row number
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row[j];
        }
        cout << endl;
    }
    cout << "  abcdefgh" << endl; 
}

std::ostream &operator<<(ostream &out, const TextDisplay &s) {
    s.print(out);
}
