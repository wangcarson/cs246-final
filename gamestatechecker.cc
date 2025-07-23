#include "gamestatechecker.h"
#include <iostream>
using namespace std;

using namespace std;

GameStateChecker::GameStateChecker(ChessBoard &b, MoveGenerator &mg): 
    board{b}, moveGenerator{mg} {}

// Checks board is valid (for setup). Outputs to standard error if invalid.
bool GameStateChecker::isValidBoard() {   
    bool whiteKing = false;
    bool blackKing = false;

    for (int i = 0; i < BOARD_COLS; ++i) {
        // check no pawns on first or last rank.
        if (board.getPiece(Tile{0, i}).isPawn() || board.getPiece(Tile{BOARD_ROWS-1, i}).isPawn()) {
            cerr << "Invalid board: Pawn is on either rank 0 or 7." << endl;
            return false;
        }

        // check no duplicate kings
        for (int j = 0; j < BOARD_ROWS; ++j) {
            Piece p = board.getPiece(Tile{i, j});
            if (p.isKing()) {
                if (p.isColour(Colour::White)) {
                    if (whiteKing) {
                        cerr << "Invalid board: Duplicate kings." << endl;
                        return false;
                    }
                    whiteKing = true;
                    
                } else if (p.isColour(Colour::Black)) {
                    if (blackKing) {
                        cerr << "Invalid board: Duplicate kings." << endl;
                        return false;
                    }
                    blackKing = true;
                }
            }
        }
    }
    // check kings exist
    if (!whiteKing || !blackKing) {
        cerr << "Invalid board: Missing king." << endl;
        return false;
    
    // check kings aren't in check.
    } else if (isCheck(Colour::White) || isCheck(Colour::Black)) {
        cerr << "Invalid board: King in check." << endl;
        return false;
    }
    return true;
}

bool GameStateChecker::isCheck(Colour c) {
    return moveGenerator.checkCheck(c);
}

bool GameStateChecker::isCheckmate(Colour c) {
    return (isCheck(c) && moveGenerator.checkNoMoves(c));
}

bool GameStateChecker::isStalemate(Colour c) {
    return (!isCheck(c) && moveGenerator.checkNoMoves(c));
}

bool GameStateChecker::isMaterialDraw() {
    std::map<char, int> pieceCounts;

    for (int i = 0; i < BOARD_ROWS; ++i) {
        for (int j = 0; j < BOARD_COLS; ++j) {
            Piece p = board.getPiece({i,j});
            // Not draw when one side has a rook, queen, or pawn.
            if (!p.isKing() && !p.isBishop() && !p.isKnight()) return false;
            ++pieceCounts[getPieceChar(p)];
        }
    }

    // Not draw when one side has two bishops or bishop + knight.
    if (pieceCounts['B'] >= 2 || // Use [] and not .at() since there may be no bishops
        pieceCounts['b'] >= 2 ||
        (pieceCounts['B'] == 1 && pieceCounts['N'] >= 1) ||
        (pieceCounts['b'] == 1 && pieceCounts['n'] >= 1)
    ) {
        return false;
    }
    return true;
}
