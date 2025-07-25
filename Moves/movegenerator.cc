#include "movegenerator.h"
#include "move.h"
#include "piece.h"
#include "tile.h"

#include <iostream>
using namespace std;

// Constructor.
MoveGenerator::MoveGenerator(ChessBoard &b, MoveMaker &mm): 
    board{b}, moveMaker{mm} {}

// Vector constants for different moves.
const vector<Tile> ROOK_VECTORS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const vector<Tile> BISHOP_VECTORS = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
const vector<Tile> ALL_VECTORS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
const vector<Tile> KNIGHT_VECTORS = {{1, -2}, {1, 2}, {-1, -2}, {-1, 2}, {-2, 1}, {2, 1}, {-2, -1}, {2, -1}};

// Constants for pawn moves.
const vector<PieceType> PROMOTION_PIECES; // = {PieceType::Queen, PieceType::Rook, PieceType::Bishop, PieceType::Knight};
const int WHITE_FORWARD = 1;
const int BLACK_FORWARD = -1;

// A function which goes down a line and checks if you can keep going or not.
// Invariant: `start` tile is non-empty and in board. 
void MoveGenerator::lineRunner(const Tile &start, const Tile &dirVector, Colour c) {    
    const Piece startPiece = board.getPiece(start);
    Tile end = start;
    end += dirVector;
    while (end.inBoard()) {
        const Piece currentPiece = board.getPiece(end);

        // add move depending on current piece.
        if (currentPiece.isColour(c)) {
            break;
        
        } else if (currentPiece.isEmpty()) {
            Move m{MoveType::Quiet, startPiece, start, end};
            pseudoMoves.emplace_back(m);
        
        } else { // opposite colour
            Move m{MoveType::Capture, startPiece, start, end};
            m.setCapturePiece(currentPiece);
            pseudoMoves.emplace_back(m);
            break;
        }

        end += dirVector;
    }
}

// For every direction vector, goes down a line and adds moves until a piece is encountered.
// Used for rook, bishop, queen.
// Invariant: `start` tile is non-empty and in board. 
void MoveGenerator::multiLineRunner(const Tile &start, const vector<Tile> &dirVectors, const Colour &c) {
    for (const auto dirVector : dirVectors) {
        lineRunner(start, dirVector, c);
    }
}

// For every move vector, adds a move if square is empty or capturable. 
// Used for knight, king.
// Invariant: `start` tile is non-empty and in board. 
void MoveGenerator::multiMoveRunner(const Tile &start, const vector<Tile> &moveVectors, const Colour &c){
    Piece startPiece = board.getPiece(start);
    for (const auto moveVector : moveVectors){
        Tile end = start + moveVector;
        
        if (end.inBoard()) {
            Piece endPiece = board.getPiece(end);

            if (endPiece.isEmpty()) {
                Move m{MoveType::Quiet, startPiece, start, end};
                pseudoMoves.emplace_back(m);

            } else if (endPiece.isOppositeColour(c)) {
                Move m{MoveType::Capture, startPiece, start, end};
                m.setCapturePiece(endPiece);
                pseudoMoves.emplace_back(m);
            }
        }
    }
}

////////////////// Moves for specific pieces ////////////////////////

// Invariant: `start` tile is non-empty and in board. 
void MoveGenerator::kingMoveGen(const Tile &start, const Colour &c){
    // regular moves.
    multiMoveRunner(start, ALL_VECTORS, c);
    
    // castling.
    Piece startPiece = board.getPiece(start);
    if (moveMaker.getCastlingRights(c, CastleType::QueenSide)) {
        Tile rookTile = Tile{start.row, 0};
        
        if (board.getPiece(rookTile).isRook() && // technically unnecessary
            board.isEmpty(Tile{start.row, 1}) && 
            board.isEmpty(Tile{start.row, 2}) && 
            board.isEmpty(Tile{start.row, 3}) &&
            start.col == 4)
        {
            Move m{MoveType::QueenSideCastle, startPiece, start, Tile{start.row, 2}};
            pseudoMoves.emplace_back(m);
        }

    } 
    if (moveMaker.getCastlingRights(c, CastleType::KingSide)) {
        Tile rookTile = Tile{start.row, 7};
        
        if (board.getPiece(rookTile).isRook() && // technically unnecessary
            board.isEmpty(Tile{start.row, 6}) && 
            board.isEmpty(Tile{start.row, 5}) && 
            start.col == 4)
        {
            Move m{MoveType::KingSideCastle, startPiece, start, Tile{start.row, 6}};
            pseudoMoves.emplace_back(m);
        }
    }
}

// Invariant: Pawns never appear on rank 0 or 7.
// Invariant: `start` tile is non-empty and in board. 
void MoveGenerator::pawnMoveGen(const Tile &start, const Colour &c) {
    bool promotionAdd = false;
    bool doublePushAdd = false;
    int forward = (c == Colour::White) ? WHITE_FORWARD : BLACK_FORWARD;
    
    // different end tiles based on colour.
    Tile pushTile = start + Tile{forward, 0};
    Tile doublePushTile = pushTile + Tile{forward, 0};

    // capture tiles.
    vector<Tile> captureTiles;
    Tile tmp = start + Tile{forward, 1};
    if (tmp.inBoard()) captureTiles.emplace_back(tmp); // write with exceptions?

    tmp = start + Tile{forward, -1};
    if (tmp.inBoard()) captureTiles.emplace_back(tmp);

    // conditions based on colour
    if (c == Colour::White) {
        if (start.row == 6) {
            promotionAdd = true;
        } else if (start.row == 1 && !board.isOccupied(doublePushTile)) {
            doublePushAdd = true;
        }

    } else if (c == Colour::Black){
        if (start.row == 1) {
            promotionAdd = true;
        } else if (start.row == 6 && !board.isOccupied(doublePushTile)) {
            doublePushAdd = true;
        }
    }

    Piece startPiece = board.getPiece(start);

    // regular moves.
    if (!board.isOccupied(pushTile)){
        if (promotionAdd) {
            // add a new move for every possible promotion
            for (const auto pieceType : PROMOTION_PIECES) {
                Move m{MoveType::Promotion, startPiece, start, pushTile};
                m.setPromotionPiece(Piece{pieceType, c});
                pseudoMoves.emplace_back(m);
            }
        
        } else {
            Move m{MoveType::Quiet, startPiece, start, pushTile};
            pseudoMoves.emplace_back(m);
        }

        if (doublePushAdd) {
            Move m{MoveType::DoublePush, startPiece, start, doublePushTile};
            pseudoMoves.emplace_back(m);
        }
    }
    
    // capture moves.
    for (auto end : captureTiles) {
        if (!end.inBoard()) { throw tile_out_of_board("pawnMoveGen end"); } // should never throw if invariants hold
        Piece endPiece = board.getPiece(end);

        if (board.isOccupied(end) && endPiece.isOppositeColour(c)) {
            if (promotionAdd) {
                for (const auto pieceType : PROMOTION_PIECES) {
                    Move m{MoveType::PromotionCapture, startPiece, start, end};
                    m.setCapturePiece(endPiece);
                    m.setPromotionPiece(Piece{pieceType, c});
                    pseudoMoves.emplace_back(m);
                }

            } else {
                Move m{MoveType::Capture, startPiece, start, end};
                m.setCapturePiece(endPiece);
                pseudoMoves.emplace_back(m);
            }
        }
    }

    // en passant.
    // Invariant: epPiece is always opponent colour (should be true) and epTile is in board
    if (moveMaker.getEnPassant().has_value()) {
        Tile epTile = moveMaker.getEnPassant().value();
        if (!epTile.inBoard()) { throw tile_out_of_board("pawnMoveGen en passant"); } // should never throw if invariants hold
        Piece epPiece = board.getPiece(epTile);

        Tile leftTile = start + Tile{0, -1};
        Tile rightTile = start + Tile{0, 1};
        if (epTile == leftTile || epTile == rightTile) {
            Move m{MoveType::EnPassant, startPiece, start, epTile + Tile{forward, 0}};
            m.setCapturePiece(epPiece);
            pseudoMoves.emplace_back(m);
        }
    }
}

// Gets all pseudo-legal moves for a piece on a tile.
// Invariant: `start` tile is non-empty and in board. 
void MoveGenerator::getPseudoMoves(const Tile &t) {
    pseudoMoves.clear();

    Colour c = board.getColour(t);
    Piece curP = board.getPiece(t);
        
    if (curP.isRook()) {
        multiLineRunner(t, ROOK_VECTORS, c);
         
    } else if (curP.isBishop()) {
        multiLineRunner(t, BISHOP_VECTORS, c);
    
    } else if (curP.isQueen()) {
        multiLineRunner(t, ALL_VECTORS, c);

    } else if (curP.isKnight()) {
        multiMoveRunner(t, KNIGHT_VECTORS, c);

    } else if (curP.isKing()) {
        kingMoveGen(t, c);

    } else if (curP.isPawn()) {
        pawnMoveGen(t, c);

    } else {
        throw invalid_argument("getPseudoMoves: called on empty square.");
    }
}

void MoveGenerator::getLegalMoves(const Tile &t, const Colour &c) {
    getPseudoMoves(t); // writes moves into `pseudoMoves` field
    
    try {
        for (const auto m : pseudoMoves) { // if it's castling, check it's check to the left + right.

            bool isCleanAlongPath = true;
            if (m.getType()==MoveType::KingSideCastle){
                //check if you are in check after moving 1 right + 2 right
                
                if (isAttacked(board.getKing(c))){
                    isCleanAlongPath=false;
                }
                moveMaker.makeMove(m);

                if (isAttacked(Tile {t.row,t.col+1})){
                    isCleanAlongPath=false;
                }
                if (isAttacked(Tile {t.row,t.col+2})){
                    isCleanAlongPath=false;
                }
                moveMaker.undoMove();

            }else if (m.getType()==MoveType::QueenSideCastle){
                //check if you are in check after moving 1 left + 2 left

                
                if (isAttacked(board.getKing(c))){
                    isCleanAlongPath=false;
                }
                moveMaker.makeMove(m);

                if (isAttacked(Tile {t.row,t.col-1})){
                    isCleanAlongPath=false;
                }
                if (isAttacked(Tile {t.row,t.col-2})){
                    isCleanAlongPath=false;
                }
                moveMaker.undoMove();

            }
            
            // check for check after move.
            moveMaker.makeMove(m);
            if (!isAttacked(board.getKing(c)) && isCleanAlongPath) {
                legalMoves.emplace_back(m);
            }
            moveMaker.undoMove();
        }
    } catch (invalid_argument &r) {
        cerr << r.what() << endl;
        cerr << "In undoMove()" << endl;
        throw;
    }
}

vector<Move> MoveGenerator::generateLegalMoves() {
    legalMoves.clear();

    Colour c = moveMaker.getTurn();
    vector<Move> legalList;    
    for (int i = 0; i < BOARD_SIZE; ++i) { // guarantees invariant that tile is in board
        for(int j = 0; j < BOARD_SIZE; ++j) {
            Tile t{i, j};
            if (c == board.getColour(t)) { // guarantees invariant that tile is nonempty
                // add legal moves for tile
                getLegalMoves(t, c);
            }
        }
    }
    return legalMoves;
}

// same as generatePseudoMoves and generateLegalMoves but breaks on legal move found. 
// a bit more efficient
bool MoveGenerator::hasNoMoves(const Colour &c) {
    legalMoves.clear();
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Tile t{i, j};
            if (c == board.getColour(t)) {
                getLegalMoves(t, c);
                if (!legalMoves.empty()) return false;
            }
        }
    }
    return true;
}

bool MoveGenerator::isAttacked(const Tile &t) {
    Colour c = board.getColour(t);
    int forward = (c == Colour::White) ? WHITE_FORWARD : BLACK_FORWARD;

    // check for opponent pawn on forward left and right tiles.
    Tile tr{t.row+forward, t.col+1};
    if (tr.inBoard()) {
        Piece p = board.getPiece(tr);
        if (p.isPawn() && p.isOppositeColour(c)) return true;
    }

    Tile tl{t.row+forward, t.col-1};
    if (tl.inBoard()) {
        Piece p = board.getPiece(tl);
        if (p.isPawn() && p.isOppositeColour(c)) return true;
    }

    // Possible bishop (and queen) spots.
    for (auto dir : BISHOP_VECTORS) {
        Tile end = t + dir;
        while (end.inBoard()) {
            const Piece p = board.getPiece(end);
            if (p.isEmpty()) {
                end += dir;
                continue;
            }
            if (p.isOppositeColour(c) && (p.isBishop() || p.isQueen())) return true;
            break;
        }
    }

    for (auto dir : ROOK_VECTORS) {
        Tile end = t + dir;
        while (end.inBoard()) {
            Piece p = board.getPiece(end);
            if (p.isEmpty()) {
                end += dir;
                continue;
            }
            if (p.isOppositeColour(c) && (p.isRook() || p.isQueen())) return true;
            break;
        }
    }

    // Possible knight spots.
    for (auto mv : KNIGHT_VECTORS) {
        Tile pos = t + mv;
        if (pos.inBoard()) {
            Piece p = board.getPiece(pos);
            if (p.isKnight() && p.isOppositeColour(c)) return true;
        }
    }

    // Possible king spots.
    for (auto mv : ALL_VECTORS) {
        Tile pos = t + mv;
        if (pos.inBoard()) {
            Piece p = board.getPiece(pos);
            if (p.isKing() && p.isOppositeColour(c)) return true;
        }
    }
    return false;
}


// m should be a legal move.
bool MoveGenerator::isCheckMove(const Move &m) {
    Colour c = m.getColour();
    moveMaker.makeMove(m);
    bool checkMove = isAttacked(board.getKing(oppositeColour(c))); // opponent in check
    moveMaker.undoMove();
    return checkMove;
}

bool MoveGenerator::isSafeMove(const Move &m) {
    moveMaker.makeMove(m);
    bool safeMove = !isAttacked(m.getTo()); // piece attacked
    moveMaker.undoMove();
    return safeMove;
}
