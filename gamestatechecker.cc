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

    return moveGenerator->findCheckMoves(c);
}

bool GameStateChecker::isMate(Colour c) {
    cout << "Checking mate" << endl;
    return isCheck(c) && moveGenerator->generatePseudoMoves(c).size() == 0;
}

bool GameStateChecker::isDraw(Colour c) {
    if (!isCheck(c) && moveGenerator->generatePseudoMoves(c).size() == 0){
        return true;
    }
    
    
    //insufficent matiral is 1 bishop/1 knight.

    vector <int> eachPieceCount;
    eachPieceCount.reserve(14);

    for(int i =0;i<8;++i){
        for(int j=0;j<8;++j){
            Tile temp {i,j};

            if (board.getColour(temp)==Colour::White){
                eachPieceCount[(int) board.getPiece(temp).type]++;
            }else if (board.getColour(temp)==Colour::Black){
                eachPieceCount[(int) board.getPiece(temp).type+7]++;
            }
            
            
        }
    }

    bool whiteInSufMat=false;
    bool blackInSufMat=false;

    if ((eachPieceCount[2]==1 && eachPieceCount[3]==1) || (eachPieceCount[9]==1 && eachPieceCount[10]==1)){
        return true;
    }

    return  eachPieceCount[0]==0 && eachPieceCount[1]==0 && eachPieceCount[2]<=1 && eachPieceCount[3]<=1 && eachPieceCount[5]==0 &&
            eachPieceCount[7]==0 && eachPieceCount[8]==0 && eachPieceCount[9]<=1 && eachPieceCount[10]<=1 && eachPieceCount[11]==0;


    


}
