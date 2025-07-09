#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>

#include <observer.h>
#include <structs.h>

class Subject {
    std::vector<Observer*> observers;
    Tile updatedTile;
  
  protected:
    void setState(Tile t);
  
  public:
    void attach(Observer *o);  
    void notifyObservers();
    Tile getState() const;
};

#endif
