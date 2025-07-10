#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>

#include "observer.h"
#include "structs.h"

class Subject {
    std::vector<Observer*> observers;
  
  public:
    void attach(Observer *o);
    void notifyObservers(Tile t); // pass info directly to observers instead of using state
};

#endif
