#include "player.h"
#include "structs.h"
using namespace std;

////////////////////////////////////////////////////////////

Player::Player(BoardManager &bm): boardManager{bm} {}
Player::~Player() {}

////////////////////////////////////////////////////////////

Human::Human(BoardManager &bm, istream &input): Player{bm}, in{input} {}

// Returns a valid move.
Move Human::getLegalMove() {
    string cmd;
    if (in.fail()) throw eof_error(); // raise exception

    while (true) {
        in >> cmd;
        if (cmd == "move") {
            string from, to;
            in >> from >> to;
            Tile start, end;
            try {
                start = parseTile(from); // add exception handling here
                end = parseTile(to);
            } catch (invalid_argument &r) {
                cerr << r.what() << endl;
                continue;
            }

            auto moves = boardManager.getMoveGenerator()->generateLegalMoves(boardManager.getMoveMaker().getTurn());
            cout << "Generate Legal Moves called:" << endl;
            cout << moves;

            for (auto it : moves) {
                if (it.getFrom() == start && it.getTo() == end) {
                    cerr << "Legal move!" << endl;
                    
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
                    	// Note: generateMoves() should only generate one move per promotion move (not one for each promotion piece type)
                    }
                    return it;
                }
            }
            cerr << "Illegal move." << endl;

        } else if (cmd == "resign") {
            throw resign_error();
        }
    }
}

////////////////////////////////////////////////////////////

Computer::Computer(BoardManager &bm, int level): Player{bm}, level{level} {}
Move Computer::getLegalMove() {
    // Actual implementation of bot goes here
    return Move();
}
