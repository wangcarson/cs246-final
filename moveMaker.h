#ifndef __MOVEMAKER_H__
#define __MOVEMAKER_H__
#include <vector>
#include <map>
#include <optional>

#include "structs.h"
#include "chessBoard.h"
#include "gameStateChecker.h"

class MoveMaker: public Subject {
    ChessBoard &board;
    GameStateChecker &stateChecker;

    std::vector<BoardState> previous;

    // board state.
    Colour turn;
    std::optional<Tile> enPassant;
    std::map<Colour, bool> castlingRights; // TODO: update to map (Colour, KingSide) -> bool
  
  public:
    MoveMaker(ChessBoard &b, GameStateChecker &gsc);
    
    void initBoardState();

    // making moves (add to previous)
    bool isLegal(Move m);
    void makeMove(Move m); // should be called on legal moves
    void undoMove();

    // board state accessors.
    Colour getTurn();
    std::optional<Tile> getEnPassant();
    bool getCastlingRights(Colour c, bool kside);

    // // board state mutators.
    void setTurn(Colour c);
    void setEnPassant(std::optional<Tile> t);
    void setCastlingRights(Colour c, bool kside, bool b);
};

#endif

void MoveMaker::initBoardState() {
  turn = Colour::White;
  enPassant = std::nullopt;
  castlingRights = {{Colour::White, true}, {Colour::Black, true}};
}
