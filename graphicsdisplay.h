#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__

#include "window.h"
#include "observer.h"
#include "structs.h"

class GraphicsDisplay: public Observer {
    Xwindow *window; // X11 graphical display

  public:
    GraphicsDisplay();
    ~GraphicsDisplay();
    void notify(Tile t) override; 
};

#endif
