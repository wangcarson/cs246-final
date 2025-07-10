#include "subject.h"
#include "structs.h"

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers(Tile t) {
    for (auto it : observers) {
        it->notify(t);
    }
}
