#include "boardmanager.h"
#include <string>
#include <iostream>
using namespace std;

const string DEFAULT_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

BoardManager::BoardManager(): board{ChessBoard{}}, moveGenerator{board}, gameStateChecker{board, moveGenerator}, moveMaker{board, gameStateChecker} {}

void BoardManager::init() {
    // initialize state
    moveMaker.initBoardState();
    
    // initialize grid to defaultx
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

ChessBoard &BoardManager::getBoard() { return board; }
GameStateChecker &BoardManager::getGameStateChecker() { return gameStateChecker; }
MoveMaker &BoardManager::getMoveMaker() { return moveMaker; }
MoveGenerator &BoardManager::getMoveGenerator() { return moveGenerator; }
