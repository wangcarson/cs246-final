#include "gamestatechecker.h"

using namespace std;

GameStateChecker::GameStateChecker(ChessBoard &b): board{b} {}
void GameStateChecker::setMG(MoveGenerator *gsc) { moveGenerator = gsc; }

// checking game states.
bool GameStateChecker::isValidBoard() {
    // loop through pieces:
    // if pawn: check none on rank 0 or 7
    // if king: ensure one king of each colour
    // check isCheck(Colour::White) and isCheck(Colour::Black)
    return true;
}

bool GameStateChecker::isCheck(Colour c) {

    //getKing
    Tile kingTile = board.getKing(c);
    vector<Move> legalList = moveGenerator->allPosibleWaysToGetToTile(kingTile,c);



    // Tile ktile = board.getKing(c);

    // check if opponent rook on same rank/file
    // bishop on diagonal
    // similar to move generation 
    return false;
}

bool GameStateChecker::isMate(Colour c) {
    return isCheck(c) && moveGenerator->generateLegalMoves(c).size() == 0;
}
bool GameStateChecker::isDraw(Colour c) {
    return !isCheck(c) && moveGenerator->generateLegalMoves(c).size() == 0;
    // todo: check for insufficient material
}
