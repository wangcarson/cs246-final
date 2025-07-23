#include "player-human.h"
using namespace std;

Human::Human(istream &input): in{input} {}

Move Human::getLegalMove(const vector<Move> &moves) const {
    string cmd;
    if (in.fail()) throw eof_error(); // raise exception

    while (true) {
        in >> cmd;
        if (cmd == "move") {
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

            for (auto it : moves) {
                if (it.getFrom() == start && it.getTo() == end) {
                    // input for promotion
                    if (it.isPromotion()) {
                        char promote;
                    	Piece p;
                    	in >> promote;
                    	try {
                            p = parsePiece(promote);
                    	} catch (invalid_argument &r) {
                            cerr << r.what() << endl;
                    		continue;
                    	}
                    	it.setPromotionPiece(p); // set promotion piece
                    }
                    cout << "Legal move!" << endl;
                    return it;
                }
            }
            cout << "Illegal move." << endl;
        
        // we have to be a bit creative with handling resign.
        } else if (cmd == "resign") {
            throw resign_error();
        
        } else if (cmd == "undo") {
            throw undo_error();
        }
    }
}
