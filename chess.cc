#include <chess.h>
using namespace std;

GameController::GameController(): mode{Mode::Normal} { // other fields are default constructed
    
}

GameController::~GameController() {
    delete whitePlayer;
    delete blackPlayer;
}

// resets fields for new game
void GameController::restart() {
    mode = Mode::Normal;
    board.init();
    delete whitePlayer;
    delete blackPlayer;
}

void GameController::start() {
    string cmd;
    board.init();

    while (true) {
        if (mode == Mode::Setup) {
            cin >> cmd;
            if (cin.fail()) break;

            if (cmd == "+") { // adding pieces
                string p, t;
                cin >> p >> t;
                try {
                    Piece piece = parsePiece(p);
                    Tile tile = parseTile(t);
                    board.addPiece(piece, tile);
                } catch (int n) {
                    cerr << "Invalid piece or square." << endl;
                }
            } else if (cmd == "-") { // removing pieces
                string s;
                cin >> s;
                try {
                    Tile t = parseTile(s);
                    board.removePiece(t);
                } catch (int n) {
                    cerr << "Invalid square." << endl;
                }
            } else if (cmd == "=") { // changing starting colour
                string c;
                cin >> c;
                if (c == "white") {
                    board.setTurn(Colour::White);
                } else if (c == "black") {
                    board.setTurn(Colour::Black);
                } else {
                    cerr << "Invalid colour." << endl;
                }
            } else if (cmd == "done") {
                if (board.isValidBoard()) {
                    mode = Mode::Normal;
                } else {
                    cerr << "Invalid board!" << endl;
                }   
            }
        } else if (mode == Mode::Game) {
            Colour c = board.getTurn();
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
            board.makeMove(m); // m is now a legal move 
            cout << td;
            if (board.isMate(Colour::White)) {
                ++whiteScore;
                restart();
            } else if (board.isMate(Colour::Black)) {
                ++blackScore;
                restart();
            } else if (board.isDraw()) {
                whiteScore += 1;
                blackScore += 1;
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

