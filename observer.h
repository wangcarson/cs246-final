#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "structs.h"

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void notify(Tile t) = 0;
};

#endif
