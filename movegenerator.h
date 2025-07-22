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

    std::vector<Move> lineRunner(Tile start, Tile dirVector, Colour c);

    std::vector<Move> multiLineRunner(Tile start, std::vector<Tile> dirVectors, Colour c);
    std::vector<Move> multiMoveRunner(Tile start, std::vector<Tile> moveVectors, Colour c);
    
    std::vector<Move> pawnMoveGen(Tile t, Colour c); // need to know last move so that we can check for en passant
    std::vector<Move> kingMoveGen(Tile t, Colour c); // need a way to check for castling

  public:
    MoveGenerator(ChessBoard &b, MoveMaker &mm);
    void setGSC(GameStateChecker *gsc);

    // bool isLegal(Move m);

    // generating moves.
    std::vector<Move> getPseudoMoves(Tile t);
    std::vector<Move> generatePseudoMoves(Colour c);
    
    // for colour.
    std::vector<Move> generateLegalMoves(Colour c);

    bool findCheckMoves(Colour c);

};

#endif
