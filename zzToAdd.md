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
- go over every method we wrote and set them to `const` or `noexcept`
- computer
- Add case in generateLegalMoves() where the move is castling. For this case, make sure the king isn't in check at any point in path. 

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
