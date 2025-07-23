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
    if (s == "h" || s == "human") {
        return new Human(boardManager, cin);
    } else if (s == "computer1" || s == "1") {
        return new Computer(boardManager, 1);
    } else if (s == "computer2" || s == "2") {
        return new Computer(boardManager, 2);
    } else if (s == "computer3" || s == "3") {
        return new Computer(boardManager, 3);
    } else if (s == "computer4" || s == "4") {
        return new Computer(boardManager, 4);
    } else {
        throw invalid_argument("Invalid player type.");
    }
}

// resets fields for new game
void GameController::restart() {
    cout << "White " << whiteScore << " - " << blackScore << " Black" << endl << endl;
    
    turnNumber = 1;
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
    cout << *td  << endl;

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
                    cout << *td << endl;
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
                    cout << *td << endl;
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
                if (boardManager.getGameStateChecker()->isValidBoard()) {
                    mode = Mode::Normal;
                    cout << "Valid board! Normal Mode" << endl;
                } else {
                    cerr << "Invalid board!" << endl;
                }   
            }

        ///////////////////////////////////////////////////////////////////
        } else if (mode == Mode::Game) {
            auto moves = boardManager.getMoveGenerator()->generateLegalMoves(boardManager.getMoveMaker().getTurn());

            debug(moves); // debugging
            cout << *td << endl;

            Colour c = boardManager.getMoveMaker().getTurn();
            Move m;
            try {
                cerr << c << " to play." << endl;
                m = (c == Colour::White) ? whitePlayer->getLegalMove(moves) : blackPlayer->getLegalMove(moves);

            } catch (eof_error &r) { // EOF: end game
                break;
            } catch (resign_error &r) {
                cerr << c << " resigned." << endl;
                if (c == Colour::White) {
                    ++blackScore;
                } else {
                    ++whiteScore;
                }
                restart();
                continue;
            } catch (undo_error &r) {
                boardManager.getMoveMaker().undoMove();                
                cout << *td << endl;
                continue;
            }

            ++turnNumber;
            boardManager.getMoveMaker().makeMove(m);

            // colour is now switched.
            c = boardManager.getMoveMaker().getTurn();
            if (boardManager.getGameStateChecker()->isCheck(c)) {
                cout << c << " is in check." << endl;
            }

            if (boardManager.getGameStateChecker()->isMate(c)) {
                cout << "Checkmate! " << c << " wins!" << endl;
                if (c == Colour::White) {
                    ++whiteScore;
                } else {
                    ++blackScore;
                }
                restart();
                
            } else if (boardManager.getGameStateChecker()->isDraw(c)) {
                cout << "Stalemate!" << endl;
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
                cout << *td << endl;

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

void GameController::debug(const vector<Move> &moves) {
    cout << "====================================" << endl;
    cout << "              TURN " << turnNumber << endl;
    cout << "====================================" << endl;
    cout << "All Legal Moves:" << endl;
    cout << moves;
    cout << "====================================" << endl;
    cout << "Current Board States:" << endl;
    auto ep = boardManager.getMoveMaker().getEnPassant();
    if (ep.has_value()) cout << "En Passant: " << ep.value() << endl;
    else cout << "En Passant: None" << endl;
    
    auto cr = boardManager.getMoveMaker().getCastlingRights();
    cout << "Castle White K: " << cr.at(Colour::White).at(CastleType::KingSide) << endl;
    cout << "Castle White Q: " << cr.at(Colour::White).at(CastleType::QueenSide) << endl;
    cout << "Castle Black K: " << cr.at(Colour::Black).at(CastleType::KingSide) << endl;
    cout << "Castle Black Q: " << cr.at(Colour::Black).at(CastleType::QueenSide) << endl;
    cout << "====================================" << endl;
}