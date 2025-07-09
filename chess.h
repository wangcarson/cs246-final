// CHESS BRAINSTORM
// (Move to separate files later)
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <optional>
using namespace std;

#include <window.h>

enum class Mode { Setup, Game, Normal };
enum class Colour { Black, White };
enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen };
enum class MoveType { Promotion, PromotionCapture, EnPassant, Capture, Castle, Regular };

struct Tile {
    int row;
    int col;
};

struct Piece { // change to class later
    PieceType type;
    Colour colour;
};

struct Move {
    MoveType type;
    Tile startTile;
    Tile endTile;
    optional<Tile> captureTile = nullopt; // for en passant
};

class Player {
  public:
    virtual void getMove() = 0;
};

class Human: public Player {
    istream &input;

  public:
    Human(istream &input);
    void getMove() override;
}; 

class Computer: public Player {
    int level;
    vector<vector<optional<Piece>>> &board;
    // private methods for computation.
  
  public:
    Computer(int level, vector<vector<optional<Piece>>> &grid);
    void getMove() override;
};

class Chessboard {
    Colour turn;
    vector<vector<optional<Piece>>> grid;
    
    // game states
    optional<Tile> enPassant; // nullopt to represent no tile
    bool castleBlack;
    bool castleWhite;
  
  public:
    Chessboard();

    void init(); // init board to default position (deallocate old data, allocate new)

    // setup mode.
    void addPiece(Piece p, Tile t);
    void removePiece(Tile t);
    void setTurn(Colour c);
    bool isValidBoard(); // verify one king each, no pawns on last rank, no checks

    // game mode.    
    bool isLegal(Move m);
    bool attemptMove(Tile start, Tile end); // verifies legal. true if success
    void makeMove(Move m);
    void undoMove(Move m);
    
    // game state.
    Tile getKing(Colour c); 
    bool isCheck(Colour c); // check
    bool isMate(Colour c); // checkmate (no moves, check)
    bool isDraw(); // stalemate (no moves, no check) or no material
    // add (private?) helper function to determine when no moves left
};

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void notify() = 0;
};

class Subject {
    vector<Observer*> observers;
    Tile updatedTile;
  
  protected:
    void setState(Tile t);
  
  public:
    void attach(Observer *o);  
    void notifyObservers();
    Tile getState() const;
};

class TextDisplay: public Observer {
    vector<vector<char>> display; // stdout display

  public:
    TextDisplay();
    void init();
    void notify() override;
    void print();
};

class GraphicsDisplay: public Observer {
    Xwindow *window; // X11 graphical display

  public:
    GraphicsDisplay();
    ~GraphicsDisplay();
    void notify() override; 
};

// implementation included as well (remove later)
// for input and output (maybe change this)
class GameController {
    Chessboard *board;
    TextDisplay *td;
    GraphicsDisplay *gd;
    
    Mode mode;
    
    istream &in;
    ostream &out;

    Player *whitePlayer = nullptr, *blackPlayer = nullptr;
    int whiteScore = 0, blackScore = 0;

    // helper functions
    void printScore();

    Piece parsePiece(string s);  // P, p, etc. to Piece()
    Tile parseTile(string s);   // eg. from 'e3' to Tile(5, 2)

    void endGame() {
        board->init();
        delete whitePlayer;
        delete blackPlayer;
    }

  public:
    GameController(istream &in, ostream &out): board{new Chessboard}, td{new TextDisplay}, gd{new GraphicsDisplay}, mode{Mode::Normal}, in{in}, out{out} {}
    ~GameController() {
        delete board;
        delete whitePlayer;
        delete blackPlayer;
    }

    void run() {
        string cmd;
        board->init();

        while (true) {
            in >> cmd;
            if (in.fail()) break;

            if (mode == Mode::Setup) {
                if (cmd == "+") {
                    string piece, square;
                    in >> piece >> square;
                    // todo

                } else if (cmd == "-") {
                    string square;
                    in >> square;
                    // todo

                } else if (cmd == "=") {
                    string c;
                    in >> c;
                    if (c == "white") {
                        board->setTurn(Colour::White);
                    } else if (c == "black") {
                        board->setTurn(Colour::Black);
                    } // if
                
                } else if (cmd == "done") {
                    if (board->isValidBoard()) {
                        mode = Mode::Normal;
                    } else {
                        out << "Invalid board!" << endl;
                    } // if
                    
                } // if
            
            } else if (mode == Mode::Game) {
                if (cmd == "move") {
                    string s, e, promote;
                    in >> s >> e;

                    // parse input and create moves
                    Tile startTile = parseTile(s); // add exception here
                    Tile endTile = parseTile(e);

                    if (board->attemptMove(startTile, endTile)) {
                        if (board->isMate(Colour::White)) {
                            // todo - change scores

                        } else if (board->isMate(Colour::White)) {
                            // todo - change scores

                        } // if

                    } // if

                } else if (cmd == "resign") {
                    // todo
                    
                } // if
            
            } else {
                if (cmd == "game") {
                    string p1, p2;
                    in >> p1 >> p2;
                    // set white_player and black_player
                    td->print();
                    mode = Mode::Game;

                } else if (cmd == "setup") {
                    mode = Mode::Setup;
                }

            } // if
        } // while
    }
};

int main() {
    GameController g(cin, cout);
    g.run();
}
