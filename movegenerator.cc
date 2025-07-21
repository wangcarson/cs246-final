#include "movegenerator.h"
using namespace std;



//A function which gose down a line and will check if you can keep going or not.
std::vector<Move> MoveGenerator::lineRunner(int rowAdd,int colAdd, Tile start, Colour c){
    vector<Move> legalList;
    
    Piece startingPiece = board.getPiece(start);

    Tile temp = start;
    temp.row+=rowAdd;
    temp.col+=colAdd;

    while(temp.col >= 0 && temp.row >= 0 && temp.col < 8 && temp.row < 8){
        Piece currentPiece = board.getPiece(temp);

        if (currentPiece.isColour(c)){
            break;
        }else if (currentPiece.isColour(Colour::None)){//None
            legalList.push_back(Move (MoveType::Quiet, startingPiece,start,temp));
        }else{
            legalList.push_back(Move (MoveType::Capture, startingPiece,start,temp));
            break;
        }

        temp.row+=rowAdd;
        temp.col+=colAdd;

    }


    return legalList;
}

vector<Move> MoveGenerator::rookLegalGen(Tile t,Colour c){
    //left, right, up, down
    vector<Move> temp0 = lineRunner(1,0,t,c);
    vector<Move> temp1 = lineRunner(-1,0,t,c);
    vector<Move> temp2 = lineRunner(0,1,t,c);
    vector<Move> temp3 = lineRunner(0,-1,t,c);

    vector<Move> legalList;

    while(!temp0.empty() && !temp1.empty() && !temp2.empty() && !temp3.empty()){
        if (!temp0.empty()){
            legalList.push_back(temp0.back());
            temp0.pop_back();
        }
        if (!temp1.empty()){
            legalList.push_back(temp1.back());
            temp1.pop_back();
        }
        if (!temp2.empty()){
            legalList.push_back(temp2.back());
            temp2.pop_back();
        }
        if (!temp3.empty()){
            legalList.push_back(temp3.back());
            temp3.pop_back();
        }

    }

    return legalList;


}

vector<Move> MoveGenerator::bishopLegalGen(Tile t,Colour c){
    //all diagonals
    vector<Move> temp0 = lineRunner(1,1,t,c);
    vector<Move> temp1 = lineRunner(-1,1,t,c);
    vector<Move> temp2 = lineRunner(-1,1,t,c);
    vector<Move> temp3 = lineRunner(-1,-1,t,c);

    vector<Move> legalList;

    while(!temp0.empty() && !temp1.empty() && !temp2.empty() && !temp3.empty()){
        if (!temp0.empty()){
            legalList.push_back(temp0.back());
            temp0.pop_back();
        }
        if (!temp1.empty()){
            legalList.push_back(temp1.back());
            temp1.pop_back();
        }
        if (!temp2.empty()){
            legalList.push_back(temp2.back());
            temp2.pop_back();
        }
        if (!temp3.empty()){
            legalList.push_back(temp3.back());
            temp3.pop_back();
        }

    }

    return legalList;
}

vector<Move> MoveGenerator::queenLegalGen(Tile t,Colour c){
    //do a legal move check using bishop + rook

    vector<Move> temp0 = rookLegalGen(t,c);
    vector<Move> temp1 = bishopLegalGen(t,c);

    vector<Move> legalList;

    while(!temp0.empty() && !temp1.empty()){
        if (!temp0.empty()){
            legalList.push_back(temp0.back());
            temp0.pop_back();
        }
        if (!temp1.empty()){
            legalList.push_back(temp1.back());
            temp1.pop_back();
        }
    }

    return legalList;

}

vector<Move> MoveGenerator::pawnLegalGen(Tile t,Colour c){//todo
    vector<Move> legalList;
    
    //2 squares diagonally, 2 squares infront.
    //consider promotions + En Passant
    if (Colour::White==c){



    }else if (Colour::Black==c){

        
    }



}

vector<Move> MoveGenerator::knightLegalGen(Tile t,Colour c){
    //hard code in all 8 squares.
    Piece startingPiece = board.getPiece(t);
    vector<Move> legalList;


    vector<int> Drow = { 1, 1, -1, -1,-2, 2, -2, 2};
    vector<int> Dcol = {-2, 2, -2, 2,  1, 1, -1, -1};

    for(int i =0;i<8;++i){
        Tile temp {t.row + Drow[i],t.col+ Dcol[i]};

        if (temp.col >= 0 && temp.row >= 0 && temp.col < 8 && temp.row < 8){

            if (!board.isOccupied(temp)){
                legalList.push_back(Move (MoveType::Quiet, startingPiece,t,temp));

            }else if (board.getColour(temp)!=c){
                legalList.push_back(Move (MoveType::Capture, startingPiece,t,temp));
            }

        }


    }

    return legalList;

}

vector<Move> MoveGenerator::kingLegalGen(Tile t,Colour c){//todo
    //all around.
    //consider castling.
}

MoveGenerator::MoveGenerator(ChessBoard &b):
    board{b} {}

vector<Move> MoveGenerator::generateLegalMoves(Colour c) {
    vector<Move> legalList;

    for(int i =0;i<8;++i){
        for(int j=0;j<8;++j){
            vector<Move> currentTileLegalMoves = getLegalMoves(Tile {i,j});
            
            while(!currentTileLegalMoves.empty()){
                legalList.push_back(currentTileLegalMoves.back());
                currentTileLegalMoves.pop_back();
            }

        }
    }

    return legalList;
}

vector<Move> MoveGenerator::getLegalMoves(Tile t) {
    Colour c = board.getColour(t);
    Piece curP = board.getPiece(t);

    if (curP.isPawn()){
        return pawnLegalGen(t,c);

    }else if (curP.isKnight()){
        return knightLegalGen(t,c);

    }else if (curP.isBishop()){
        return bishopLegalGen(t,c);

    }else if (curP.isQueen()){
        return queenLegalGen(t,c);

    }else if (curP.isRook()){
        return rookLegalGen(t,c);

    }else if (curP.isKing()){
        return kingLegalGen(t,c);

    }

}
