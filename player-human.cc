#include "player-human.h"
using namespace std;

Human::Human(istream &input,Colour color): in{input},color{color} {}

// Gets a legal move from standard input.
Move Human::getLegalMove(const vector<Move> &legalMoves) const {
    string cmd;
    if (in.fail()) throw eof_error(); // raise exception

    while (true) {
        in >> cmd;
        if (cmd == "move") {
            // get move from standard input.

            string from, to;
            in >> from >> to;
            Tile start, end;
            try {
                start = parseTile(from);
                end = parseTile(to);
            } catch (invalid_argument &r) {
                cerr << r.what() << endl; // give feedback and continue
                continue;
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
                    	Piece p;
                    	in >> promote;

                    	try {
                            p = parsePiece(promote);
                            p.colour = color;
                    	} catch (invalid_argument &r) {
                            cerr << r.what() << endl;
                    		continue; // TODO: this continue doesn't actually work as intended
                    	}

                        if (p.type!= PieceType::Queen || p.type!= PieceType::Rook || p.type!= PieceType::Bishop || p.type!= PieceType::Knight){
                            cerr << "Illegal promotion, defult promotion." <<endl;
                            p.type = PieceType::Queen;
                        }

                        
                    	it.setPromotionPiece(p); // set promotion piece
                    }
                    // cerr << "Legal move!" << endl;
                    return it;
                }
            }
            cerr << "Illegal move. Please enter another move." << endl;
        
        // we have to be a bit creative with handling resign.
        } else if (cmd == "resign") {
            throw input_resign();
        
        } else if (cmd == "undo") {
            throw input_undo();
        }
    }
}
