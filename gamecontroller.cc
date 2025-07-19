#include "gamecontroller.h"
using namespace std;

GameController::GameController(): mode{Mode::Normal}, boardManager{}, td{boardManager}, gd{boardManager} { // other fields are default constructed
    boardManager.init();
}

GameController::~GameController() {
    delete whitePlayer;
    delete blackPlayer;
}

// Get player object corresponding to s. Allocates dynamic memory.
Player *GameController::getPlayer(string s) {
    if (s == "human") {
        return new Human(boardManager, cin);
    } else if (s == "computer1") {
        return new Computer(boardManager, 1);
    } else if (s == "computer2") {
        return new Computer(boardManager, 2);
    } else if (s == "computer3") {
        return new Computer(boardManager, 3);
    } else if (s == "computer4") {
        return new Computer(boardManager, 4);
    } else {
        throw DEFAULT_ERROR;
    }
}

// resets fields for new game
void GameController::restart() {
    mode = Mode::Normal;
    boardManager.init();
    delete whitePlayer;
    delete blackPlayer;
}

void GameController::start() {
    string cmd;
    boardManager.init();

    while (true) {
        if (mode == Mode::Setup) {
            cin >> cmd;
            if (cin.fail()) break;

            if (cmd == "+") { // adding pieces
                char p;
                string t;
                cin >> p >> t;
                try {
                    Piece piece = parsePiece(p);
                    Tile tile = parseTile(t);
                    boardManager.getBoard().setPiece(tile, piece);
                } catch (int n) {
                    cerr << "Invalid piece or square." << endl;
                }
            } else if (cmd == "-") { // removing pieces
                string s;
                cin >> s;
                try {
                    Tile t = parseTile(s);
                    boardManager.getBoard().removePiece(t);
                } catch (int n) {
                    cerr << "Invalid square." << endl;
                }
            } else if (cmd == "=") { // changing starting colour
                string c;
                cin >> c;
                if (c == "white") {
                    boardManager.getMoveMaker().setTurn(Colour::White);
                } else if (c == "black") {
                    boardManager.getMoveMaker().setTurn(Colour::Black);
                } else {
                    cerr << "Invalid colour." << endl;
                }
            } else if (cmd == "done") {
                if (boardManager.getGameStateChecker().isValidBoard()) {
                    mode = Mode::Normal;
                } else {
                    cerr << "Invalid board!" << endl;
                }   
            }
        } else if (mode == Mode::Game) {
            Colour c = boardManager.getMoveMaker().getTurn();
            Move m;
            if (c == Colour::White) { // get move from player
                try {
                    m = whitePlayer->getLegalMove();
                } catch (int error) { // EOF or resign
                    if (error == EOF_ERROR) break;
                    else if (error == RESIGN_ERROR) {
                        ++blackScore;
                        restart();
                    }
                }
            } else {
                try {
                    m = blackPlayer->getLegalMove();
                } catch (int error) {
                    if (error == EOF_ERROR) break;
                    else if (error == RESIGN_ERROR) {
                        ++whiteScore;
                        restart();
                    }
                }
            }
            boardManager.getMoveMaker().makeMove(m); // m is now a legal move 
            cout << td;
            if (boardManager.getGameStateChecker().isMate(c)) {
                if (c == Colour::White) {
                    ++whiteScore;
                } else {
                    ++blackScore;
                }
                restart();
                
            } else if (boardManager.getGameStateChecker().isDraw(c)) {
                whiteScore += 0.5;
                blackScore += 0.5;
                restart();
            }
        } else {
            cin >> cmd;
            if (cin.fail()) break;

            if (cmd == "game") {
                string p1, p2;
                cin >> p1 >> p2;
                
                whitePlayer = getPlayer(p1); // pick human or computer
                blackPlayer = getPlayer(p2);

                mode = Mode::Game;
                cout << td;

            } else if (cmd == "setup") {
                mode = Mode::Setup;
            }
        }
    }

    // print scores on break
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;
}

