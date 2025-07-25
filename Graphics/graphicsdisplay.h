#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__

#include "tile.h"
#include "boardmanager.h"
#include "observer.h"
#include "window.h"

class GraphicsDisplay: public Observer {
    ChessBoard &board;
    std::unique_ptr<Xwindow> window; // X11 graphical display

  public:
    GraphicsDisplay(ChessBoard &b);
    void notify(Tile t) override; 
};

#endif
