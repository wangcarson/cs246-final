#include "movegenerator.h"
using namespace std;

// Constructor.
MoveGenerator::MoveGenerator(ChessBoard &b, MoveMaker &mm): board{b}, moveMaker{mm} {}
void MoveGenerator::setGSC(GameStateChecker *gsc) { gameStateChecker = gsc; }

// making moves (add to previous)
bool MoveGenerator::isLegal(Move m) {
    moveMaker.makeMove(m);
    bool legal = !gameStateChecker->isCheck(m.getColour());
    moveMaker.undoMove();
    return legal;
}

// A function which goes down a line and checks if you can keep going or not.
// Invariant: Called on non-empty `start` tile
vector<Move> MoveGenerator::lineRunner(Tile start, Tile dirVector, Colour c) {
    const Piece startPiece = board.getPiece(start);

    vector<Move> legalList;
    Tile end = start;
    end += dirVector;

    while (end.inBoard()){
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

// VECTOR CONSTANTS FOR DIFFERENT PIECES
const vector<Tile> ROOK_VECTORS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const vector<Tile> BISHOP_VECTORS = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
const vector<Tile> KNIGHT_VECTORS = {
    {1, -2}, {1, 2}, {-1, -2}, {-1, 2}, 
    {-2, 1}, {2, 1}, {-2, -1}, {2, -1}
};

vector<Move> MoveGenerator::rookLegalGen(Tile start, Colour c) {
    vector<Move> legalList;
    for (const auto dirVector : ROOK_VECTORS) {
        vector<Move> dirMoves = lineRunner(start, dirVector, c);

        // append items in temp to legalList
        legalList.insert(legalList.end(), dirMoves.begin(), dirMoves.end());
    }
    return legalList;
}

vector<Move> MoveGenerator::bishopLegalGen(Tile t, Colour c){
    vector<Move> legalList;
    for (const auto lineVector : BISHOP_VECTORS) {
        vector<Move> dirMoves = lineRunner(t, lineVector, c);

        // append items in temp to legalList
        legalList.insert(legalList.end(), dirMoves.begin(), dirMoves.end());
    }
    return legalList;
}

vector<Move> MoveGenerator::queenLegalGen(Tile start, Colour c){
    // add legal moves of rook and bishop
    vector<Move> rookMoves = rookLegalGen(start, c);
    vector<Move> bishopMoves = bishopLegalGen(start, c);
    
    vector<Move> legalList;
    legalList.insert(legalList.end(), rookMoves.begin(), rookMoves.end());
    legalList.insert(legalList.end(), bishopMoves.begin(), bishopMoves.end());
    return legalList;
}

vector<Move> MoveGenerator::knightLegalGen(Tile start, Colour c){
    vector<Move> legalList;
    Piece startPiece = board.getPiece(start);

    for (const auto moveVector : KNIGHT_VECTORS){
        Tile end = start + moveVector;
        
        if (end.inBoard()){
            Piece endPiece = board.getPiece(end);

            if (endPiece.isEmpty()) {
                Move m{MoveType::Quiet, startPiece, start, end};
                legalList.emplace_back(m);

            } else if (endPiece.isOppositeColour(c)) { // new function just adds exception throwing in case
                Move m{MoveType::Capture, startPiece, start, end};
                m.setCapturePiece(endPiece);
                legalList.emplace_back(m);
            }
        }
    }
    return legalList;
}

// Constants
const vector<PieceType> PROMOTION_PIECES = {PieceType::Queen, PieceType::Rook, PieceType::Bishop, PieceType::Knight};
const int WHITE_FORWARD = 1;
const int BLACK_FORWARD = -1;

// Invariant: Pawns never appear on rank 0 or 7.
vector<Move> MoveGenerator::pawnLegalGen(Tile start, Colour c) {
    vector<Move> legalList;
    bool promotionAdd = false;
    bool doublePushAdd = false;
    int forward = (c == Colour::White) ? WHITE_FORWARD : BLACK_FORWARD;
    
    // different end tiles based on colour
    Tile pushTile = start + Tile{forward, 0};
    Tile doublePushTile = pushTile + Tile{forward, 0};
    vector<Tile> captureTiles = {start + Tile{forward, 1}, start + Tile{forward, -1}};

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
        
        } else if (doublePushAdd) {
            Move m{MoveType::DoublePush, startPiece, start, pushTile};
            legalList.emplace_back(Move (MoveType::DoublePush, startPiece, start, doublePushTile));
                
        } else {
            Move m{MoveType::Quiet, startPiece, start, pushTile};
            legalList.emplace_back(Move (MoveType::Quiet, startPiece, start, pushTile));
        }
    }
    
    // capture moves.
    for (auto end : captureTiles) {
        Piece endPiece = board.getPiece(end);

        if (board.isOccupied(end) && board.getColour(end) == Colour::Black) {
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
    return legalList;
}

vector<Move> MoveGenerator::kingLegalGen(Tile t, Colour c){ // todo

    Piece startPiece = board.getPiece(t);
    vector<Move> legalList;


    vector<int> Drow = {1, 1,-1,-1,1, 1,-1,-1};
    vector<int> Dcol = {1,-1, 1,-1,1,-1, 1,-1};

    for(int i =0;i<8;++i){
        Tile temp {t.row + Drow[i],t.col+ Dcol[i]};

        if (temp.col >= 0 && temp.row >= 0 && temp.col < 8 && temp.row < 8){

            if (!board.isOccupied(temp)) {
                legalList.emplace_back(Move (MoveType::Quiet, startPiece,t,temp));

            } else if (board.getColour(temp)!=c) {
                legalList.emplace_back(Move (MoveType::Capture, startPiece,t,temp));
            }

        }

    }

    // need to add  a test for castling. Aka casting is still allowed


    return legalList;
}

vector<Move> MoveGenerator::generateLegalMoves(Colour c) {
    vector<Move> legalList;

    for(int i = 0; i < BOARD_ROWS; ++i){
        for(int j = 0; j < BOARD_COLS; ++j) {
            Tile t{i, j};
            if (c == board.getColour(t)) {
                vector<Move> currentTileLegalMoves = getLegalMoves(t);

                // add to legal list
                while (!currentTileLegalMoves.empty()){
                    legalList.emplace_back(currentTileLegalMoves.back());
                    currentTileLegalMoves.pop_back();
                }
            }
        }
    }
    return legalList;
}

vector<Move> MoveGenerator::getLegalMoves(Tile t) {
    Colour c = board.getColour(t);
    Piece curP = board.getPiece(t);

    if (curP.isPawn()){
        return pawnLegalGen(t, c);

    } else if (curP.isKnight()){
        return knightLegalGen(t, c);

    } else if (curP.isBishop()){
        return bishopLegalGen(t, c);

    } else if (curP.isQueen()){
        return queenLegalGen(t, c);

    } else if (curP.isRook()){
        return rookLegalGen(t, c);

    } else if (curP.isKing()){
        return kingLegalGen(t, c);

    } else {
        throw invalid_argument("getLegalMoves: called on empty square.");
    }
}
