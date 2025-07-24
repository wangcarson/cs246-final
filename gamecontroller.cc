#include "gamecontroller.h"
#include "player-human.h"
#include "player-computer.h"
#include <stdexcept>
#include "evaluation.h"
#include "puzzle.h"

#include "player-engine.h"
using namespace std;

GameController::GameController(istream &in, bool debug, bool useGD): in{in}, debug{debug}, useGD{useGD} { // other fields are default constructed
    td = make_unique<TextDisplay>(boardManager.getBoard());
    if (useGD) {
        gd = make_unique<GraphicsDisplay>(boardManager.getBoard()); // optional with tag
        boardManager.getBoard().attach(gd.get());
    }
    boardManager.getBoard().attach(td.get());
    
    // initialize maps.
    players.emplace(Colour::White, nullptr);
    players.emplace(Colour::Black, nullptr);
    scores.emplace(Colour::White, 0);
    scores.emplace(Colour::Black, 0);
}

// Creates a Player object corresponding to string `s`.
// Returns as a smart pointer (transfers ownership).
unique_ptr<Player> GameController::getPlayer(string s,Colour c) {
    if (s == "h" || s == "human") {
        return make_unique<Human>(in, c);
    } else if (s == "computer1" || s == "1") {
        return make_unique<Computer>(1, boardManager);
    } else if (s == "computer2" || s == "2") {
        return make_unique<Computer>(2, boardManager);
    } else if (s == "computer3" || s == "3") {
        return make_unique<Computer>(3, boardManager);
    } else if (s == "computer4" || s == "4") {
        return make_unique<Engine>(boardManager);
    } else {
        throw invalid_argument("Invalid player: " + s);
    }
}

// Resets states for new game.
void GameController::resetState() {
    cout << "White " << scores.at(Colour::White) << " - " << scores.at(Colour::Black) << " Black" << endl << endl;
    cout << endl << ">>> Normal Mode <<<" << endl;

    // reset states.
    mode = Mode::Normal;
    players.at(Colour::White).reset(); // deallocates memory
    players.at(Colour::Black).reset();
    turnNumber = 1;
    boardManager.init();
}

// Input management and error handling for program.
void GameController::runGame() {
    // initialize board and print.
    // boardManager.init();
    try { boardManager.init(); }
    catch (...) {
        throw runtime_error("GameController::start(): Error with initializing board");
    }
    cout << endl << "Starting program..." << endl;
    cout << *td  << endl;
    cout << endl << ">>> Normal Mode <<<" << endl;
    
    string cmd;
    while (true) {
        // setup mode.
        if (mode == Mode::Setup) {
            in >> cmd;
            if (in.fail()) break;

            if (cmd == "+") { // adding pieces
                char p;
                string t;
                in >> p >> t;
                try {
                    Piece piece = parsePiece(p);
                    Tile tile = parseTile(t);
                    boardManager.getBoard().setPiece(tile, piece);
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                } catch (...) {
                    cerr << "+: Error" << endl;
                }
                cout << *td << endl;
                
            } else if (cmd == "-") { // removing pieces
                string s;
                in >> s;
                try {
                    Tile t = parseTile(s);
                    boardManager.getBoard().removePiece(t);
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                } catch (...) {
                    cerr << "-: Error" << endl;
                }
                cout << *td << endl;
            
            } else if (cmd == "=") { // changing starting colour
                string c;
                in >> c;
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
                    cout << endl << ">>> Normal Mode <<<" << endl;
                } else {
                    cerr << "Please correct the board before exiting setup." << endl;
                }
            }

        // game mode.
        } else if (mode == Mode::Game) {
            Colour turn = boardManager.getMoveMaker().getTurn();
            Colour opponent = oppositeColour(turn);
            auto legalMoves = boardManager.getMoveGenerator().generateLegalMoves();
            
            // output board and debug info
            printData(legalMoves);
            cout << turn << " to play." << endl;
            auto player = players.at(turn).get();
            
            Move m;
            try {
                m = player->getLegalMove(legalMoves);
            } catch (eof_error &r) {
                break;

            } catch (input_resign &r) {
                cerr << turn << " resigned. " << opponent << " wins!" << endl;
                ++scores.at(opponent);
                resetState();
                continue;
            
            } catch (input_undo &r) {
                --turnNumber;             
                boardManager.getMoveMaker().undoMove();
                continue;
            }

            // make the move.
            ++turnNumber;
            boardManager.getMoveMaker().makeMove(m);

            // colour is now switched.
            if (boardManager.getGameStateChecker().isCheck(opponent)) {
                cout << opponent << " is in check." << endl;
            }

            if (boardManager.getGameStateChecker().isCheckmate(opponent)) {
                cout << *td << endl;
                cout << "Checkmate! " << turn << " wins!" << endl;
                ++scores.at(turn);
                resetState();
                continue;
                
            } else if (boardManager.getGameStateChecker().isStalemate(opponent)) {
                cout << *td << endl;
                cout << "Stalemate!" << endl;
                scores.at(turn) += 0.5;
                scores.at(opponent) += 0.5;
                resetState();
                continue;
            
            } else if (boardManager.getGameStateChecker().isMaterialDraw()) {
                cout << *td << endl;
                cout << "Draw by insufficient material!" << endl;
                scores.at(turn) += 0.5;
                scores.at(opponent) += 0.5;
                resetState();
                continue;
            }
        
        // puzzle mode.
        } else if (mode == Mode::Puzzle) {
            // do computer move first.
            auto moves = boardManager.getMoveGenerator().generateLegalMoves();
            Move response = puzzle->getResponseMove(moves);
            boardManager.getMoveMaker().makeMove(response);
            cout << "Computer moves " << response << endl;
            cout << *td << endl;
            cout << boardManager.getMoveMaker().getTurn() << " to move." << endl;

            // do human player moves.
            moves = boardManager.getMoveGenerator().generateLegalMoves();
            Move play;
            while (true) {
                try {
                    play = puzzlePlayer->getLegalMove(moves);
                } catch (eof_error &r) {
                    break;
                } catch (...) {
                    continue;
                }
                // verify correct move.
                if (puzzle->isCorrectMove(play)) {
                    break;
                }
                cout << "Incorrect move! Try again." << endl;
            }
            // make move.
            boardManager.getMoveMaker().makeMove(play);
            cout << "Correct!" << endl;
            cout << *td << endl;

            try { 
                puzzle->loadMoves();
            } catch (eof_error &r) { // puzzle finished
                cout << "Puzzle completed!" << endl;
                mode = Mode::Normal;
                cout << endl << ">>> Normal Mode <<<" << endl;
            }
        
        // default mode
        } else if (mode == Mode::Normal) {
            in >> cmd;
            if (in.fail()) break;

            // starting a new game.
            if (cmd == "game") {
                string p1, p2;
                in >> p1 >> p2;
                try {
                    players.at(Colour::White) = getPlayer(p1,Colour::White); // gets either human or computer
                    players.at(Colour::Black) = getPlayer(p2,Colour::Black);
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                    continue;
                }
                cout << endl << ">>> Game Mode <<<" << endl;
                mode = Mode::Game;

            } else if (cmd == "setup") {
                cout << endl << ">>> Setup Mode <<<" << endl;
                mode = Mode::Setup;
            
            // starting a new puzzle.
            } else if (cmd == "puzzle") {
                cout << endl << ">>> Puzzle Mode <<<" << endl;
                puzzlePlayer = make_unique<Human>(in,Colour::White);
                puzzle = make_unique<Puzzle>();
                mode = Mode::Puzzle;

                // setup puzzle.
                cout << "Setting up puzzle..." << endl;
                string p = puzzle->getPosition();
                boardManager.init(p);
                cout << *td << endl;
                puzzle->loadMoves();
            }
        }
    } // while loop breaks on EOF

    // print scores
    cout << "Final Score:" << endl;
    cout << "White: " << scores.at(Colour::White) << endl;
    cout << "Black: " << scores.at(Colour::Black) << endl;
}

//  Prints board info for debugging.
const string &bar = "=====================================";
void GameController::printData(const vector<Move> &moves) {
    cout << endl << bar << endl;
    cout << "              TURN " << turnNumber << endl;
    cout << bar << endl;

    if (debug) {
        cout << "All Legal Moves:" << endl;
        cout << moves;
        cout << bar << endl;
        cout << "Current Board States:" << endl;
        auto ep = boardManager.getMoveMaker().getEnPassant();
        if (ep.has_value()) cout << "En Passant: " << ep.value() << endl;
        else cout << "En Passant: None" << endl;
        
        auto cr = boardManager.getMoveMaker().getCastlingRights();
        cout << "Castle White K: " << cr.at(Colour::White).at(CastleType::KingSide) << endl;
        cout << "Castle White Q: " << cr.at(Colour::White).at(CastleType::QueenSide) << endl;
        cout << "Castle Black K: " << cr.at(Colour::Black).at(CastleType::KingSide) << endl;
        cout << "Castle Black Q: " << cr.at(Colour::Black).at(CastleType::QueenSide) << endl;
        cout << bar << endl;
    }
    
    cout << *td << endl << endl;
    cout << "Evaluation: " << getEvaluationValue(boardManager) << endl;
}
