#include "graphicsdisplay.h"
using namespace std;

const int WINDOW_SIZE = 500;
const int SQUARE_SIZE = 50;
const int MARGIN = (WINDOW_SIZE - BOARD_COLS*SQUARE_SIZE)/2;

GraphicsDisplay::GraphicsDisplay(ChessBoard &b): board{b}, window{make_unique<Xwindow>(WINDOW_SIZE, WINDOW_SIZE)} {
    window->fillRectangle(0, 0, WINDOW_SIZE, WINDOW_SIZE, Xwindow::Blue);
}

void GraphicsDisplay::notify(Tile t) {
    auto squareColour = (t.row+t.col) % 2 == 0 ? Xwindow::Black : Xwindow::White;
    auto pieceColour = (t.row+t.col) % 2 == 0 ? Xwindow::White : Xwindow::Black;
    int left = MARGIN + t.col*SQUARE_SIZE;
    int top = MARGIN + t.row*SQUARE_SIZE;

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
        window->drawString(left+SQUARE_SIZE/2 - 1, top+SQUARE_SIZE/2 + 1, ch, pieceColour);
    }
}


