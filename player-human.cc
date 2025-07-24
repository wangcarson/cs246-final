#include "player-human.h"
using namespace std;

Human::Human(istream &input,Colour color): in{input},color{color} {}

// Gets a legal move from standard input.
Move Human::getLegalMove(const vector<Move> &legalMoves) const {
    string from, to;
    in >> from >> to;
    Tile start, end;
    try { // get input and parse.
        start = parseTile(from);
        end = parseTile(to);
    } catch (invalid_argument &r) {
        cerr << r.what() << endl; // give feedback and throw
        throw invalid_move();
    }

    // to determine if the input move is legal,
    // check if the move is in the provided `legalMoves` vector.

    // this way, if the move is legal, it already comes with all 
    // necessary data for the move (move type, tiles, pieces).
    Move legalMove;
    for (auto it : legalMoves) {
        if (start == it.getFrom() && end == it.getTo()) {
            // case for promotion move.
            if (it.isPromotion()) {
                char promote;
                in >> promote;
                Piece p;
                try { // get input and parse.
                    p = parsePiece(promote);
                    p.colour = color;
                } catch (invalid_argument &r) {
                    cerr << r.what() << endl;
                    throw invalid_move();
                }
                if (p.type!= PieceType::Queen || p.type!= PieceType::Rook || p.type!= PieceType::Bishop || p.type!= PieceType::Knight){
                    cerr << "Illegal promotion piece." <<endl;
                    throw invalid_move();
                }
                it.setPromotionPiece(p); // set promotion piece
            }
            return it;
        }   
    }
    // illegal move.
    cerr << "Illegal move. Please enter another move." << endl;
    throw illegal_move();
}
