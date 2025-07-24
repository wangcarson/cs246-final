# Currently working on
movegenerator.cc

# NEW! Changes:
- new fields for different player types
- getLegalMove() for players now takes a vector argument for all legal moves (optimizes it a bit since it prevents generateLegalMoves() from being called more than once every round)
- so, player no longer needs BoardManager

#### USE -d TAG FOR DEBUGGING ####
- setCapturePiece() in move did nothing before - changed
- fixed capture and castle restoration in undoMove()
- added en passant restoration in undoMove()
- bug in capture moves for pawn in MoveGenerator

# Things to do
- change player pointers to smart pointers (and remove dtors - extra credit)
- Add case in generateLegalMoves() where the move is castling. For this case, make sure the king isn't in check at any point in path. 
- computer
- graphics display
- puzzle shuffle
-when we setup a board it should remain.
-if type just move bot make a move for us.
-needs to say check when the king is in check
-game 4 4 bug
-something about bot level 4 needs fixing to many random moves spazing out
-add error checking for Colour's on promotion.
-UML update
-documnetation update.

# optimizations
- check no memory is leaked
- go over every method we wrote and set them to `const` or `noexcept`
- for debugging: rewrite Tile ctor to force row and col in [0, 7] - exception otherwise (to 100% make sure we never segmentation fault)
- keep a piece list (or at least vars for kings)

# Finished tasks
- separate players.cc and players.h into 6 files
- add big 5 ctors to Piece struct since we need move ctor. (we just use default move ctor since Piece has no fields with dynamic memory)

- GameStateChecker::isValidBoard()
- Bot::getLegalMove()
if a king moves both types of castling are no longer allowed. (DONE)
if a rook moves that sides castling is now illegal. (DONE)
- GameStateChecker::isCheck()
- GameStateChecker::isDraw() - check for insufficient material
- MoveMaker::undoMove()
