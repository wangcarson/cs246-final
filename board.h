#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <optional>
#include <map>

#include "structs.h"
#include "window.h"
#include "subject.h"

class Board: public Subject {
    Colour turn;
    std::vector<std::vector<std::optional<Piece>>> position;
    
    // game states
    std::optional<Tile> enPassant; // nullopt to represent no tile
    std::map<Colour, bool> castlingRights;

    std::vector<TurnData> previousMoves;
  
  public:
    Board();

    void init(); // init board to default position (deallocate old data, allocate new)

    // setup mode. (should call observers)
    void setPiece(Tile t, Piece p);
    void removePiece(Tile t);
    void setTurn(Colour c);
    Colour getTurn();
    bool isValidBoard(); // verify one king each, no pawns on last rank, no checks

    // game mode.    
    bool isLegal(Move m);
    void makeMove(Move m); // should be called on legal moves
    void undoMove(Move m);

    std::vector<Move> generateMoves(); // maybe cache
    
    // game state.
    Tile getKing(Colour c); 
    bool isCheck(Colour c); // check
    bool isMate(Colour c); // checkmate (no moves, check)
    bool isDraw(); // stalemate (no moves, no check) or no material
    // add (private?) helper function to determine when no moves left
};

#endif
