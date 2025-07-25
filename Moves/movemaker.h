#ifndef __MOVEMAKER_H__
#define __MOVEMAKER_H__
#include <vector>
#include <map>
#include <optional>

#include "structs.h"
#include "chessboard.h" 

class MoveMaker: public Subject {
    ChessBoard &board;

    std::vector<MoveData> previous;

    // board state.
    Colour turn;
    std::optional<Tile> enPassant;
    std::map<Colour, std::map<CastleType, bool>> castlingRights;
  
  public:
    MoveMaker(ChessBoard &b);
    
    void initBoardState(Colour starting=Colour::White);

    // making moves (add to previous)
    void makeMove(Move m, bool official=false); // should be called on legal moves
    void undoMove(bool official=false);

    // board state accessors.
    Colour getTurn() const noexcept;
    std::optional<Tile> getEnPassant() const noexcept;
    std::map<Colour, std::map<CastleType, bool>> getCastlingRights() const noexcept;
    bool getCastlingRights(Colour c, CastleType s) const;

    // // board state mutators.
    void setTurn(Colour c);
    void setEnPassant(std::optional<Tile> t);
    void setCastlingRights(std::map<Colour, std::map<CastleType, bool>> castlingRights);
    void setCastlingRights(Colour c, CastleType s, bool b);
};

#endif
