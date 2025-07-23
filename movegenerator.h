#ifndef __MOVEGENERATOR_H__
#define __MOVEGENERATOR_H__

#include "structs.h"
#include "chessboard.h"
#include "movemaker.h"
#include "gamestatechecker.h"

class GameStateChecker; // forward declaration

class MoveGenerator {
    ChessBoard &board;
    MoveMaker &moveMaker;

    std::vector<Move> lineRunner(Tile start, Tile dirVector, Colour c);

    std::vector<Move> multiLineRunner(Tile start, std::vector<Tile> dirVectors, Colour c);
    std::vector<Move> multiMoveRunner(Tile start, std::vector<Tile> moveVectors, Colour c);
    
    std::vector<Move> pawnMoveGen(Tile t, Colour c); // need to know last move so that we can check for en passant
    std::vector<Move> kingMoveGen(Tile t, Colour c); // need a way to check for castling

    // generating moves.
    std::vector<Move> getPseudoMoves(Tile t);
    std::vector<Move> getLegalMoves(Tile t, Colour c);

  public:
    MoveGenerator(ChessBoard &b, MoveMaker &mm);
    
    // for colour.
    std::vector<Move> generateLegalMoves(Colour c);

    // used by GameStateChecker.
    bool isAttacked(Tile t); // used by check and isSafeMove()
    bool checkNoMoves(Colour c);

    // used by Computer.
    bool isCheckMove(Move m);
    bool isSafeMove(Move m);
};

#endif
