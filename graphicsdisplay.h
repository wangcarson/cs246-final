#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__

#include "structs.h"
#include "boardmanager.h"
#include "observer.h"
#include "window.h"

class GraphicsDisplay: public Observer {
    BoardManager &boardManager;
    Xwindow *window; // X11 graphical display

  public:
    GraphicsDisplay(BoardManager bm);
    ~GraphicsDisplay();
    void notify(Tile t) override; 
};

#endif
