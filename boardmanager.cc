#include "boardmanager.h"
#include <string>
#include <iostream>
using namespace std;

const string DEFAULT_POSITION = "rnbqkbnr/pppppppp/11111111/11111111/11111111/11111111/PPPPPPPP/RNBQKBNR";

// Constructor.
BoardManager::BoardManager(): 
    moveMaker{board}, 
    moveGenerator{board, moveMaker}, 
    gameStateChecker{board, moveGenerator} {}

// Initializing state and board.
void BoardManager::init() {
    // initialize state
    moveMaker.initBoardState();
    
    // initialize grid to default
    board.clearGrid();
    int row = 0, col = 0;
    for (char c : DEFAULT_POSITION) {
        if (c == '/') {
            row++;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            board.setPiece(Tile{BOARD_ROWS-row-1, col}, parsePiece(c)); // at() raises error if not found
            col++;
        }
    }
}

// Accessors for classes.
ChessBoard &BoardManager::getBoard() { return board; }
MoveMaker &BoardManager::getMoveMaker() { return moveMaker; }
MoveGenerator &BoardManager::getMoveGenerator() { return moveGenerator; }
GameStateChecker &BoardManager::getGameStateChecker() { return gameStateChecker; }
