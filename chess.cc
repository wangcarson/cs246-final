#include <chess.h>
using namespace std;

void GameController::start() {
    string cmd;
    board->init();

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
                    board->addPiece(piece, tile);
                } catch (int n) {
                    cerr << "Invalid piece or square." << endl;
                }
            } else if (cmd == "-") { // removing pieces
                string s;
                cin >> s;
                try {
                    Tile t = parseTile(s);
                    board->removePiece(t);
                } catch (int n) {
                    cerr << "Invalid square." << endl;
                }
            } else if (cmd == "=") { // changing starting colour
                string c;
                cin >> c;
                if (c == "white") {
                    try {
                        board->setTurn(Colour::White);
                    } catch (int n) { // EOF
                        break;
                    }
                } else if (c == "black") {
                    try {
                        board->setTurn(Colour::Black);
                    } catch (int n) { // EOF
                        break;
                    }
                } else {
                    cerr << "Invalid colour." << endl;
                }
            } else if (cmd == "done") {
                if (board->isValidBoard()) {
                    mode = Mode::Normal;
                } else {
                    cerr << "Invalid board!" << endl;
                }
                
            }
        
        } else if (mode == Mode::Game) {
            Colour c = board->getTurn();
            Move m;
            if (c == Colour::White) { // get move from player
                m = whitePlayer->getMove();
            } else {
                m = blackPlayer->getMove();
            }

            if (board->isLegal(m)) { // check if legal
                board->makeMove(m);  // make move if yes 
                cout << td;
                if (board->isMate(Colour::White)) {
                    ++whiteScore;
                    restart();
                } else if (board->isMate(Colour::Black)) {
                    ++blackScore;
                    restart();
                } else if (board->isDraw()) {
                    whiteScore += 1;
                    blackScore += 1;
                    restart();
                }
            }
        
        } else {
            cin >> cmd;
            if (cin.fail()) break;

            if (cmd == "game") {
                string p1, p2;
                cin >> p1 >> p2;
                
                whitePlayer = new Human(cin); // todo: pick human or computer
                blackPlayer = new Human(cin);

                cout << td;
                mode = Mode::Game;

            } else if (cmd == "setup") {
                mode = Mode::Setup;
            }

        }
    }

    // print scores
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;

}

void GameController::restart() {
    mode = Mode::Normal;
    board->init();
    delete whitePlayer;
    delete blackPlayer;
}
