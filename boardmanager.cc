#include "boardmanager.h"
#include <string>
using namespace std;

const int BOARD_SIZE = 8;
const string DEFAULT_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

BoardManager::BoardManager(): board{}, moveGenerator{board}, gameStateChecker{board, moveGenerator}, moveMaker{board, gameStateChecker} {}

void BoardManager::init() {
    // initialize state
    moveMaker.initBoardState();

    // initialize grid to default (import FEN)
    board.clearGrid();
    int row = 0, col = 0;
    for (char c : DEFAULT_POSITION) {
        if (c == '/') {
            row++;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            board.setPiece(Tile{row, col}, CHAR_PIECE_MAP.at(c)); // at() raises error if not found
        }
    }
}

ChessBoard BoardManager::getBoard() { return board; }
GameStateChecker BoardManager::getGameStateChecker() { return gameStateChecker; }
MoveMaker BoardManager::getMoveMaker() { return moveMaker; }
MoveGenerator BoardManager::getMoveGenerator() { return moveGenerator; }
