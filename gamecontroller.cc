#include "gamecontroller.h"
#include "player-human.h"
#include "player-computer.h"
#include <stdexcept>
#include "evaluation.h"
#include "puzzle.h"

#include "player-engine.h"
using namespace std;

GameController::GameController(istream &in, bool debug, bool useGD, bool largeTD, bool autoMovementForBot): 
in{in}, debug{debug}, useGD{useGD}, largeTD{largeTD}, autoMovementForBot{autoMovementForBot} { // other fields are default constructed
    puzzle = make_unique<Puzzle>();

    td = make_unique<TextDisplay>(boardManager.getBoard(), largeTD);
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
    cout << "White " << scores.at(Colour::White) << " - " << scores.at(Colour::Black) << " Black" << endl;
    cout << endl << ">>> Normal Mode <<<" << endl;

    // reset states.
    mode = Mode::Normal;
    players.at(Colour::White).reset();
    players.at(Colour::Black).reset();
    turnNumber = 1;
}

// Input management and error handling for program.
void GameController::runGame() {
    // initialize board and print.
    try { boardManager.init(FenString); }
    catch (...) {
        throw runtime_error("GameController::start(): Error with initializing board");
    }
    cout << "Starting program..." << endl;
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
                    boardManager.getBoard().setPiece(tile, piece, true);
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                    continue;
                }
                cout << *td << endl;
                
            } else if (cmd == "-") { // removing pieces
                string s;
                in >> s;
                try {
                    Tile t = parseTile(s);
                    boardManager.getBoard().removePiece(t, true);
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                    continue;
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
                    FenString = boardManager.boardToFen(); //updates fen string
                    cout << endl << ">>> Normal Mode <<<" << endl;
                    
                } else {
                    cerr << "Please correct the board before exiting setup." << endl;
                }
            }

        // game mode.
        } else if (mode == Mode::Game) {
            if (!autoMovementForBot){
                in >> cmd;
                if (in.fail()) break;
            }
            
            // get turn info.
            Colour turn = boardManager.getMoveMaker().getTurn();
            Colour opponent = oppositeColour(turn);
            auto player = players.at(turn).get();

            // get a move from player.
            Move m;
            if (cmd == "resign") {
                cerr << turn << " resigned. " << opponent << " wins!" << endl;
                ++scores.at(opponent);
                resetState();
                continue;
            
            } else if (cmd == "undo") {
                --turnNumber;             
                boardManager.getMoveMaker().undoMove(true);
                cachedLegalMoves = boardManager.getMoveGenerator().generateLegalMoves();
                printData(cachedLegalMoves);
                continue;
            
            } else if (autoMovementForBot || cmd == "move") {
                try { m = player->getLegalMove(cachedLegalMoves); } // get legal move from player.
                catch (...) { continue; }                           // skip if invalid move.

                // make the move and print.
                ++turnNumber;
                boardManager.getMoveMaker().makeMove(m, true);

                // print board.
                cachedLegalMoves = boardManager.getMoveGenerator().generateLegalMoves();
                printData(cachedLegalMoves);

                // check for game end.
                if (boardManager.getGameStateChecker().isCheck(opponent)) {
                    cout << opponent << " is in check." << endl;
                }
                if (boardManager.getGameStateChecker().isCheckmate(opponent)) {
                    cout << "Checkmate! " << turn << " wins!" << endl;
                    ++scores.at(turn);
                    resetState();
                    continue;
                    
                } else if (boardManager.getGameStateChecker().isStalemate(opponent)) {
                    cout << "Stalemate!" << endl;
                    scores.at(turn) += 0.5;
                    scores.at(opponent) += 0.5;
                    resetState();
                    continue;
                
                } else if (boardManager.getGameStateChecker().isMaterialDraw()) {
                    cout << "Draw by insufficient material!" << endl;
                    scores.at(turn) += 0.5;
                    scores.at(opponent) += 0.5;
                    resetState();
                    continue;
                }

                // print new turn.
                cout << opponent << " to play." << endl;
        
            // we have to be a bit creative with handling resign.
            }
        
        // puzzle mode.
        } else if (mode == Mode::Puzzle) {
            // do computer move first.
            cachedLegalMoves = boardManager.getMoveGenerator().generateLegalMoves();
            Move response = puzzle->getResponseMove(cachedLegalMoves);
            boardManager.getMoveMaker().makeMove(response, true);
            cout << "Computer moves " << response << endl;
            cout << *td << endl;
            cout << boardManager.getMoveMaker().getTurn() << " to move." << endl;

            // do human player moves.
            Move m;
            cachedLegalMoves = boardManager.getMoveGenerator().generateLegalMoves();
            bool eof_break = false;
            while (true) {
                in >> cmd;
                if (in.fail()) {
                    eof_break = true;
                    break;
                }
                
                if (cmd == "move") {
                    try { m = puzzlePlayer->getLegalMove(cachedLegalMoves); } // get legal move from player.
                    catch (...) { continue; }                                 // skip if invalid move.

                    if (puzzle->isCorrectMove(m)) { // exit loop if correct move.
                        break;
                    }
                    cout << "Incorrect move! Try again." << endl;
                }
            }
            if (eof_break) break; // break twice on EOF

            // make move.
            boardManager.getMoveMaker().makeMove(m, true);
            cout << "Correct!" << endl;
            cout << *td << endl;

            try { 
                puzzle->loadMoves();
            } catch (puzzle_end &r) { // puzzle finished
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
                try { boardManager.init(FenString); }
                catch (...) {
                    throw runtime_error("GameController::runGame(): Error with initializing board");
                }
                cachedLegalMoves = boardManager.getMoveGenerator().generateLegalMoves();
                printData(cachedLegalMoves);
                cout << boardManager.getMoveMaker().getTurn() << " to play." << endl;

            } else if (cmd == "setup") {
                cout << endl << ">>> Setup Mode <<<" << endl;
                cout << *td << endl;
                mode = Mode::Setup;
            
            // starting a new puzzle.
            } else if (cmd == "puzzle") {
                cout << endl << ">>> Puzzle Mode <<<" << endl;
                mode = Mode::Puzzle;
                
                // setup puzzle.
                cout << "Setting up puzzle..." << endl;
                string p = puzzle->getPosition();
                
                puzzlePlayer = make_unique<Human>(in,p.back() == 'w' ? Colour::White : Colour::Black);

                try { boardManager.init(p); }
                catch (...) {
                    throw runtime_error("GameController::runGame(): Error with initializing puzzle board");
                }
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
        cout << "Evaluation: " << getEvaluationValue(boardManager) << endl;
    }
    cout << *td << endl << endl;
}
