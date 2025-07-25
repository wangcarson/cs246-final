#include "graphicsdisplay.h"
using namespace std;

const int WINDOW_SIZE = 500;
const int SQUARE_SIZE = 50;
const int MARGIN = (WINDOW_SIZE - BOARD_SIZE*SQUARE_SIZE)/2;
const int TEXT_OFFSET = 1;

GraphicsDisplay::GraphicsDisplay(ChessBoard &b): board{b}, window{make_unique<Xwindow>(WINDOW_SIZE, WINDOW_SIZE)} {
    // fill background and draw labels
    window->fillRectangle(0, 0, WINDOW_SIZE, WINDOW_SIZE, Xwindow::Blue);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        string s = to_string(i+1);
        int top = WINDOW_SIZE - MARGIN - (i+1)*SQUARE_SIZE;
        window->drawString(MARGIN/2, top+SQUARE_SIZE/2 + TEXT_OFFSET, s, Xwindow::Black);

        char c = 'a' + i;
        s = c;
        int left = MARGIN + i*SQUARE_SIZE;
        window->drawString(left+SQUARE_SIZE/2 - TEXT_OFFSET, WINDOW_SIZE-MARGIN/2, s, Xwindow::Black);
    }
}

void GraphicsDisplay::notify(Tile t) {
    auto squareColour = (t.row+t.col) % 2 == 0 ? Xwindow::Black : Xwindow::White;
    auto pieceColour = (t.row+t.col) % 2 == 0 ? Xwindow::White : Xwindow::Black;
    int left = MARGIN + t.col*SQUARE_SIZE;
    int top = WINDOW_SIZE - MARGIN - (t.row+1)*SQUARE_SIZE;

    window->fillRectangle(left, top, SQUARE_SIZE, SQUARE_SIZE, squareColour);
    
    if (board.isOccupied(t)) {
        Piece p = board.getPiece(t);
        string ch;
        try { ch = getPieceChar(p); }
        catch (invalid_argument &r) {
            cerr << r.what() << endl;
            cerr << "called with tile " << t << endl;
            throw;
        }
        window->drawString(left+SQUARE_SIZE/2 - TEXT_OFFSET, top+SQUARE_SIZE/2 + TEXT_OFFSET, ch, pieceColour);
    }
}


