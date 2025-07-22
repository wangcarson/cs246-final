#include "gamestatechecker.h"
#include <iostream>
using namespace std;

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
    // Tile ktile = board.getKing(c);
    // check if opponent rook on same rank/file
    // bishop on diagonal
    // similar to move generation 

    return moveGenerator->isCheckMG(c);
}

bool GameStateChecker::isMate(Colour c) {
    cout << "Checking mate" << endl;
    return isCheck(c) && moveGenerator->sudoMovesGen(c).size() == 0;
}

bool GameStateChecker::isDraw(Colour c) {
    return !isCheck(c) && moveGenerator->sudoMovesGen(c).size() == 0;
    // todo: check for insufficient material
    
    //insufficent matiral is 1 bishop/1 knight.

    vector<Piece> matrialInPlay;
    vector <int> eachPieceCount;
    eachPieceCount.reserve(14);

    for(int i =0;i<8;++i){
        for(int j=0;j<8;++j){
            Tile temp {i,j};

            eachPieceCount[(int) board.getPiece(temp).type]++;
            
            
        }
    }
//enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty };

    


}
