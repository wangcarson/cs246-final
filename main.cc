#include <iostream>
#include <string>
#include "gamecontroller.h"

int main(int argc, char* argv[]) {
    // command line arguments.
    bool debug = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-debug" || arg == "-d") {
            debug = true;
        }
    }

    GameController g{debug};
    g.start();
}
