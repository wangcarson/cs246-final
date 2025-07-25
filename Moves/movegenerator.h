#ifndef __MOVEGENERATOR_H__
#define __MOVEGENERATOR_H__
#include "move.h"
#include "tile.h"
#include "chessboard.h"
#include "movemaker.h"

class MoveGenerator {
    ChessBoard &board;
    MoveMaker &moveMaker;

    std::vector<Move> pseudoMoves;
    std::vector<Move> legalMoves;

    void lineRunner(const Tile &start, const Tile &dirVector, Colour c);

    void multiLineRunner(const Tile &start, const std::vector<Tile> &dirVectors, const Colour &c);
    void multiMoveRunner(const Tile &start, const std::vector<Tile> &moveVectors, const Colour &c);
    
    void pawnMoveGen(const Tile &start, const Colour &c); // need to know last move so that we can check for en passant
    void kingMoveGen(const Tile &start, const Colour &c); // need a way to check for castling

    // generating moves.
    void getPseudoMoves(const Tile &t);
    void getLegalMoves(const Tile &t, const Colour &c);

  public:
    MoveGenerator(ChessBoard &b, MoveMaker &mm);
    
    // for current colour.
    std::vector<Move> generateLegalMoves(); // returns copy, not reference

    // used by GameStateChecker.
    bool isAttacked(const Tile &t); // used by check and isSafeMove()
    bool hasNoMoves(const Colour &c);

    // used by Computer.
    bool isCheckMove(const Move &m);
    bool isSafeMove(const Move &m);
};

#endif
