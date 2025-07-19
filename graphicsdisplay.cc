#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(BoardManager bm): boardManager{bm}, window{new Xwindow} {}

GraphicsDisplay::~GraphicsDisplay() { delete window; }

void GraphicsDisplay::notify(Tile t) {
    // Piece p = boardManager.getBoard().getPiece(t);
}


