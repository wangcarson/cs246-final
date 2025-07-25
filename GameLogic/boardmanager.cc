#include "boardmanager.h"
#include <string>
#include <iostream>
using namespace std;

// Constructor.
BoardManager::BoardManager(): 
    moveMaker{board}, 
    moveGenerator{board, moveMaker}, 
    gameStateChecker{board, moveGenerator} {}

// Initializing state and board.
void BoardManager::init(string position) {
    // initialize state
    char c = position.back();
    Colour starting;
    if (c == 'w') starting = Colour::White;
    else if (c == 'b') starting = Colour::Black;
    else throw invalid_argument("FEN string has invalid colour.");
    moveMaker.initBoardState(starting);
    
    // initialize grid to default
    position.pop_back();
    position.pop_back();
    board.clearGrid();
    int row = 0, col = 0;
    for (char c : position) {
        if (c == '/') {
            row++;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            board.setPiece(Tile{BOARD_SIZE-row-1, col}, parsePiece(c), true);
            col++;
        }
    }
}

// Accessors for classes.
ChessBoard &BoardManager::getBoard() { return board; }
MoveMaker &BoardManager::getMoveMaker() { return moveMaker; }
MoveGenerator &BoardManager::getMoveGenerator() { return moveGenerator; }
GameStateChecker &BoardManager::getGameStateChecker() { return gameStateChecker; }

std::string BoardManager::boardToFen(){
    std::string fenString="";
    int skip =0;

    for(int row =7;row>=0;--row){
        for(int col=0;col<8;++col){
            
            char toUseInString = getPieceChar(board.getPiece(Tile {row,col}));

            if (toUseInString==' '){
                ++skip;
            }else if (skip>0){
                char alpha = (char)(skip+48);
                fenString+=alpha;
                fenString+=toUseInString;
                skip=0;
            }else{
                fenString+=toUseInString;
            }


        }
        if (skip>0){
            char alpha = (char)(skip+48);
            fenString+=alpha;
            skip=0;
        }
        if (row>0){
            fenString+='/';
        }
    }

    if (board.getTurn()==Colour::Black){
        fenString+=" b";
    }else{
        fenString+=" w";
    }

    return fenString;
}
