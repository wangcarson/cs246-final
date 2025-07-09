#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void notify() = 0;
};

#endif
