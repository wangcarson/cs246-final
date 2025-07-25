#include "subject.h"
using namespace std;
#include <iostream>

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers(Tile t) {
    for (auto it : observers) {
        it->notify(t);
    }
}
