#include "movegenerator.h"
#include "structs.h"

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
const vector<PieceType> PROMOTION_PIECES = {PieceType::Queen, PieceType::Rook, PieceType::Bishop, PieceType::Knight};
const int WHITE_FORWARD = 1;
const int BLACK_FORWARD = -1;

// A function which goes down a line and checks if you can keep going or not.
// Invariant: `start` tile is non-empty and in board. 
vector<Move> MoveGenerator::lineRunner(Tile start, Tile dirVector, Colour c) {
    const Piece startPiece = board.getPiece(start);

    vector<Move> legalList;
    Tile end = start;
    end += dirVector;

    while (end.inBoard()) {
        const Piece currentPiece = board.getPiece(end);

        // add move depending on current piece.
        if (currentPiece.isColour(c)){
            break;
        
        } else if (currentPiece.isEmpty()){
            Move m{MoveType::Quiet, startPiece, start, end};
            legalList.emplace_back(m);
        
        } else { // opposite colour
            Move m{MoveType::Capture, startPiece, start, end};
            m.setCapturePiece(currentPiece);
            legalList.emplace_back(m);
            break;
        }

        end += dirVector;
    }
    return legalList;
}

// For every direction vector, goes down a line and adds moves until a piece is encountered.
// Used for rook, bishop, queen.
// Invariant: `start` tile is non-empty and in board. 
vector<Move> MoveGenerator::multiLineRunner(Tile start, vector<Tile> dirVectors, Colour c) {
    vector<Move> legalList;
    for (const auto dirVector : dirVectors) {
        vector<Move> dirMoves = lineRunner(start, dirVector, c);

        // append items to legalList
        legalList.insert(legalList.end(), dirMoves.begin(), dirMoves.end());
    }
    return legalList;
}

// For every move vector, adds a move if square is empty or capturable. 
// Used for knight, king.
// Invariant: `start` tile is non-empty and in board. 
vector<Move> MoveGenerator::multiMoveRunner(Tile start, vector<Tile> moveVectors, Colour c){
    vector<Move> legalList;
    Piece startPiece = board.getPiece(start);

    for (const auto moveVector : moveVectors){
        Tile end = start + moveVector;
        
        if (end.inBoard()) {
            Piece endPiece = board.getPiece(end);

            if (endPiece.isEmpty()) {
                Move m{MoveType::Quiet, startPiece, start, end};
                legalList.emplace_back(m);

            } else if (endPiece.isOppositeColour(c)) {
                Move m{MoveType::Capture, startPiece, start, end};
                m.setCapturePiece(endPiece);
                legalList.emplace_back(m);
            }
        }
    }
    return legalList;
}

////////////////// Moves for specific pieces ////////////////////////

// Invariant: `start` tile is non-empty and in board. 
vector<Move> MoveGenerator::kingMoveGen(Tile start, Colour c){ // todo
    // regular moves.
    Piece startPiece = board.getPiece(start);

    vector<Move> legalList = multiMoveRunner(start, ALL_VECTORS, c);

    // castling.
    if (moveMaker.getCastlingRights(c, CastleType::QueenSide)) { // TODO: can abstract later
        Tile rookTile = Tile{start.row, 0};
        
        if (board.getPiece(rookTile).isRook() && // technically unnecessary
            board.isEmpty(Tile{start.row, 1}) && 
            board.isEmpty(Tile{start.row, 2}) && 
            board.isEmpty(Tile{start.row, 3}) &&
            start.col == 4)
        {
            Move m{MoveType::QueenSideCastle, startPiece, start, rookTile};
        }

    } else if (moveMaker.getCastlingRights(c, CastleType::KingSide)) {
        Tile rookTile = Tile{start.row, 7};
        
        if (board.getPiece(rookTile).isRook() && // technically unnecessary
            board.isEmpty(Tile{start.row, 6}) && 
            board.isEmpty(Tile{start.row, 5}) && 
            start.col == 4)
        {
            Move m{MoveType::KingSideCastle, startPiece, start, rookTile};
        }
    }
    return legalList;
}

// Invariant: Pawns never appear on rank 0 or 7.
// Invariant: `start` tile is non-empty and in board. 
vector<Move> MoveGenerator::pawnMoveGen(Tile start, Colour c) {
    vector<Move> legalList;
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
                legalList.emplace_back(m);
            }
        
        } else {
            Move m{MoveType::Quiet, startPiece, start, pushTile};
            legalList.emplace_back(m);
        }

        if (doublePushAdd) {
            Move m{MoveType::DoublePush, startPiece, start, doublePushTile};
            legalList.emplace_back(m);
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
                    legalList.emplace_back(m);
                }

            } else {
                Move m{MoveType::Capture, startPiece, start, end};
                m.setCapturePiece(endPiece);
                legalList.emplace_back(m);
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
            legalList.emplace_back(m);
        }
    }

    return legalList;
}

// Gets all pseudo-legal moves for a piece on a tile.
// Invariant: `start` tile is non-empty and in board. 
vector<Move> MoveGenerator::getPseudoMoves(Tile t) {
    Colour c = board.getColour(t);
    Piece curP = board.getPiece(t);
        
    if (curP.isRook()) {
        return multiLineRunner(t, ROOK_VECTORS, c);
         
    } else if (curP.isBishop()) {
        return multiLineRunner(t, BISHOP_VECTORS, c);
    
    } else if (curP.isQueen()) {
        return multiLineRunner(t, ALL_VECTORS, c);

    } else if (curP.isKnight()) {
        return multiMoveRunner(t, KNIGHT_VECTORS, c);

    } else if (curP.isKing()) {
        return kingMoveGen(t, c);

    } else if (curP.isPawn()) {
        return pawnMoveGen(t, c);

    } else {
        throw invalid_argument("getPseudoMoves: called on empty square.");
    }
}

vector<Move> MoveGenerator::getLegalMoves(Tile t, Colour c) {
    vector<Move> legalList;
    vector<Move> pseudoList = getPseudoMoves(t);
    try {
        for (const auto m : pseudoList) {
            moveMaker.makeMove(m);
            if (!checkCheck(c)) {
                legalList.emplace_back(m);
            }
            moveMaker.undoMove();
        }
    } catch (invalid_argument &r) {
        cerr << r.what() << endl;
        cerr << "In undoMove()" << endl;
        throw;
    }
    return legalList;
}

vector<Move> MoveGenerator::generateLegalMoves(Colour c) {
    vector<Move> legalList;
    for (int i = 0; i < BOARD_ROWS; ++i) { // guarantees invariant that tile is in board
        for(int j = 0; j < BOARD_COLS; ++j) {
            Tile t{i, j};
            if (c == board.getColour(t)) { // guarantees invariant that tile is nonempty
                // add legal moves for tile
                vector<Move> curLegalMoves = getLegalMoves(t, c);
                legalList.insert(legalList.end(), curLegalMoves.begin(), curLegalMoves.end());
            }
        }
    }
    return legalList;
}

// same as generatePseudoMoves and generateLegalMoves but breaks on legal move found. 
// a bit more efficient
bool MoveGenerator::checkNoMoves(Colour c) {
    for (int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            Tile t{i, j};
            if (c == board.getColour(t) && getLegalMoves(t, c).size() != 0) {
                return false;
            }
        }
    }
    return true;
}

bool MoveGenerator::checkCheck(Colour c) {
    Tile t = board.getKing(c);
    int forward = (c == Colour::White) ? WHITE_FORWARD : BLACK_FORWARD;

    // check for opponent pawn on forward left and right tiles.
    Tile tr{t.row+forward, t.col+1};
    if (tr.inBoard()) {
        Piece trPiece = board.getPiece(tr);
        if (trPiece.isPawn() && trPiece.isOppositeColour(c)){
            return true;
        }
    }

    Tile tl{t.row+forward, t.col-1};
    if (tl.inBoard()) {
        Piece tlPiece = board.getPiece(tl);
        if (tlPiece.isPawn() && tlPiece.isOppositeColour(c)){
            return true;
        }
    }

    // Possible bishop (and queen) spots.
    vector<Move> bishopSpots = multiLineRunner(t, BISHOP_VECTORS, c);
    for (auto possibleMove : bishopSpots) {
        if (possibleMove.isCapture() && (possibleMove.getCapturePiece().isBishop() || possibleMove.getCapturePiece().isQueen())) {
            return true;
        }
    }

    // Possible rook (and queen) spots.
    vector<Move> rookSpots = multiLineRunner(t, ROOK_VECTORS, c);
    for (auto possibleMove : rookSpots) {
        if (possibleMove.isCapture() && (possibleMove.getCapturePiece().isRook() || possibleMove.getCapturePiece().isQueen())) {
            return true;
        }
    }

    // Possible knight spots.
    vector<Move> knightSpots = multiMoveRunner(t, KNIGHT_VECTORS, c);
    for (auto possibleMove : knightSpots) {
        if (possibleMove.isCapture() && possibleMove.getCapturePiece().isKnight()) {
            return true;
        }
    }

    // Possible king spots.
    vector<Move> kingSpots = multiMoveRunner(t, ALL_VECTORS, c);
    for (auto possibleMove : kingSpots) {
        if (possibleMove.isCapture() && possibleMove.getCapturePiece().isKing()) {
            return true;
        }
    }

    return false;
}
