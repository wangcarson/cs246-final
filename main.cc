#include <iostream>
#include <string>
#include "gamecontroller.h"

int main(int argc, char* argv[]) {
    // command line arguments.
    bool debug = false;
    bool gd = false;
    bool autoMovementForBot = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-d") {
            debug = true;
        } else if (arg == "-g") {
            gd = true;
        }else if (arg == "-auto"){
            autoMovementForBot=true;
        }
    }

    GameController g(std::cin, debug, gd,autoMovementForBot);
    g.runGame();
}
