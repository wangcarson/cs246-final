#include "movegenerator.h"
using namespace std;


vector<Move> MoveGenerator::pawnLegalGen(Tile t,Colour c){
    vector<Move> legalList;

    //2 squares diagonally, 2 squares infront.

    if (Colour::White==c){


    }else if (Colour::Black==c){

        
    }



}
vector<Move> MoveGenerator::rookLegalGen(Tile t,Colour c){
    //left, right, up, down
}
vector<Move> MoveGenerator::queenLegalGen(Tile t,Colour c){
    //do a legal move check using bishop + rook
}
vector<Move> MoveGenerator::knightLegalGen(Tile t,Colour c){
    //hard code in all 8 squares.
}
vector<Move> MoveGenerator::bishopLegalGen(Tile t,Colour c){
    //all diagonals
}
vector<Move> MoveGenerator::kingLegalGen(Tile t,Colour c){
    //all around.
}

MoveGenerator::MoveGenerator(ChessBoard &b):
    board{b} {}

vector<Move> MoveGenerator::generateLegalMoves(Colour c) {
    vector<Move> allLegalMoves;
    vector<Move> currentTileLegalMoves;

    for(int i =0;i<8;++i){
        for(int j=0;j<8;++j){

            Tile cur{i,j};

            Piece curP = board.getPiece(cur);

            if (curP.isPawn()){
                currentTileLegalMoves = pawnLegalGen(cur,c);
            }else if (curP.isKnight()){

            }else if (curP.isBishop()){

            }else if (curP.isQueen()){

            }else if (curP.isRook()){

            }else if (curP.isKing()){
                currentTileLegalMoves = pawnLegalGen(cur,c);

            }else{
                //this means we shouldn't be conserned about it and the spot is empty
            }

        }
    }

    // todo
    return vector<Move>();
}

vector<Move> MoveGenerator::getLegalMoves(Tile t) {
    // todo
    return vector<Move>();
}
