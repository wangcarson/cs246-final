#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector>
#include <iostream>

#include <observer.h>

class TextDisplay: public Observer {
    std::vector<std::vector<char>> display; // stdout display

  public:
    TextDisplay();
    void init();
    void notify() override;
    void print();
};
#endif
