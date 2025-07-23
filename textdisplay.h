#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector>
#include <iostream>

#include "structs.h"
#include "chessboard.h"
#include "observer.h"

class TextDisplay: public Observer {
    ChessBoard &board;
    std::vector<std::vector<char>> display; // stdout display

  public:
    TextDisplay(ChessBoard &b); // explicit?
    void notify(Tile t) override;
    void print(std::ostream &out) const;
    void printLarge(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &s);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &s);

#endif
