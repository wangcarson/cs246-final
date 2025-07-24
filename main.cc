#include <iostream>
#include <string>
#include "gamecontroller.h"

int main(int argc, char* argv[]) {
    // command line arguments.
    bool debug = false;
    bool showGD = false;
    bool largeTD = false;
    bool autoMovementForBot = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-d") {
            debug = true;
        } else if (arg == "-g") {
            showGD = true;
        } else if (arg == "-t") {
            largeTD = true;
        } else if (arg == "-auto"){
            autoMovementForBot=true;
        }
    }

    GameController g(std::cin, debug, showGD, largeTD, autoMovementForBot);
    g.runGame();
}
