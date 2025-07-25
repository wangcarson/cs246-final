#ifndef __MOVEMAKER_H__
#define __MOVEMAKER_H__
#include <vector>
#include <map>
#include <optional>
#include "move.h"
#include "tile.h"
#include "chessboard.h" 

class MoveMaker: public Subject {
    ChessBoard &board;

    
    // board state.
    Colour turn;
    std::optional<Tile> enPassant;
    // std::map<Colour, std::map<CastleType, bool>> castlingRights;
    bool castleRightWK;
    bool castleRightWQ;
    bool castleRightBK;
    bool castleRightBQ;

    void setCastlingRights(Colour c, bool b);
    void setCastlingRights(Colour c, CastleType s, bool b);
    
  public:
    std::vector<MoveData> previous;
    MoveMaker(ChessBoard &b);
    
    // initializing board state.
    void initBoardState(Colour starting=Colour::White);

    // making moves.
    void makeMove(const Move &m, bool official=false); // official moves notify display observers
    void undoMove(bool official=false);

    // board state accessors.
    Colour getTurn() const noexcept;
    std::optional<Tile> getEnPassant() const noexcept;
    bool getCastlingRights(Colour c, CastleType s) const;

    // board state mutators.
    void setTurn(Colour c); // called in setup mode
};

#endif
