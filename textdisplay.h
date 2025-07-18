#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector>
#include <iostream>

#include "structs.h"
#include "boardManager.h"
#include "observer.h"

class TextDisplay: public Observer {
    BoardManager boardManager;
    std::vector<std::vector<char>> display; // stdout display

  public:
    TextDisplay(BoardManager bm);
    void notify(Tile t) override;
    void print(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &s);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &s);

#endif
