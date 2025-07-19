#include "gamecontroller.h"
#include <stdexcept>
using namespace std;

GameController::GameController(): 
mode{Mode::Normal}, boardManager{}, td{new TextDisplay{boardManager.getBoard()}} /*, gd{boardManager}*/ { // other fields are default constructed
    boardManager.getBoard().attach(td);
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
        throw invalid_argument("Invalid player type.");
    }
}

// resets fields for new game
void GameController::restart() {
    cout << "White " << whiteScore << " - " << blackScore << " Black" << endl;
    cout << endl;
    
    mode = Mode::Normal;
    boardManager.init();
    delete whitePlayer;
    delete blackPlayer;
}

void GameController::start() {
    string cmd;
    try {
        boardManager.init(); // add error handling
        cerr << "Board initialized!" << endl;
    } catch (...) {
        cerr << "start(): Error with initializing board" << endl;
    }
    cout << *td; // print!

    cout << "Normal Mode" << endl;
    while (true) {
        ///////////////////////////////////////////////////////////////////
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
                    cout << *td;
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                } catch (...) {
                    cerr << "+: Error" << endl;
                }
            
            } else if (cmd == "-") { // removing pieces
                string s;
                cin >> s;
                try {
                    Tile t = parseTile(s);
                    boardManager.getBoard().removePiece(t);
                    cout << *td;
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                } catch (...) {
                    cerr << "-: Error" << endl;
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
                    cout << "Valid board! Normal Mode" << endl;
                } else {
                    cerr << "Invalid board!" << endl;
                }   
            }

        ///////////////////////////////////////////////////////////////////
        } else if (mode == Mode::Game) {
            Colour c = boardManager.getMoveMaker().getTurn();
            Move m;
            if (c == Colour::White) { // get move from player
                try {
                    cerr << "White to play." << endl;
                    m = whitePlayer->getLegalMove();
                } catch (eof_error &r) { // EOF: end game
                    break;
                } catch (resign_error &r) {
                    cerr << "White resigned. Black wins." << endl;
                    ++blackScore;
                    restart();
                    continue;
                }
            } else {
                try {
                    cerr << "Black to play." << endl;
                    m = blackPlayer->getLegalMove();
                } catch (eof_error &r) { // EOF
                    break;
                } catch (resign_error &r) {
                    cerr << "Black resigned. White wins." << endl;
                    ++whiteScore;
                    restart();
                    continue;
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
        
        ///////////////////////////////////////////////////////////////////
        } else {
            cin >> cmd;
            if (cin.fail()) break;

            if (cmd == "game") {
                string p1, p2;
                cin >> p1 >> p2;
                try {
                    whitePlayer = getPlayer(p1); // pick human or computer
                    blackPlayer = getPlayer(p2);
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                    continue;
                }

                mode = Mode::Game;
                cout << "Game Mode" << endl;
                cout << *td;

            } else if (cmd == "setup") {
                mode = Mode::Setup;
                cout << "Setup Mode" << endl;
            }
        }
    }

    // print scores on break
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;
}

