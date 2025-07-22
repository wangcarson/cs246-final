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
    GameStateChecker *gameStateChecker = nullptr;

    std::vector<Move> lineRunner(Tile start, Tile vector, Colour c);
    
    std::vector<Move> pawnLegalGen(Tile t, Colour c); // need to know last move so that we can check for en passant
    std::vector<Move> rookLegalGen(Tile t, Colour c);
    std::vector<Move> queenLegalGen(Tile t, Colour c);
    std::vector<Move> knightLegalGen(Tile t, Colour c);
    std::vector<Move> bishopLegalGen(Tile t, Colour c);
    std::vector<Move> kingLegalGen(Tile t, Colour c); // need a way to check for castling

  public:
    MoveGenerator(ChessBoard &b, MoveMaker &mm);
    void setGSC(GameStateChecker *gsc);

    bool isLegal(Move m);

    // generating moves.
    std::vector<Move> generateLegalMoves(Colour c); //without castling or en passon.
    std::vector<Move> getLegalMoves(Tile t);
};

#endif
