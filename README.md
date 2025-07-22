# Chess Final Project CS246
UML: https://app.diagrams.net/#G1lRNCI3E9-eA93eCA1ebcU7ZRArMRj4mN#%7B%22pageId%22%3A%22jKWO1p7c0j1E2HtElivG%22%7D

Dependency order:
structs
window
observer
subject
textdisplay
graphicsdisplay
player
board
chess
main

# Explanation:

`Chessboard` is just the board representation.
It gives functionality for adding and removing pieces, as well as accessing board information.

The board is a vector of `Piece` objects.
Each `Piece` object contains a `PieceType` and `Colour`.
To help with board representation, a `Tile` structure containing an integer pair 
is used to represent a position on the board.

`MoveMaker` gives functionality for making and undoing movings.
It handles board state (castling rights, en passant) and keeps track of previous moves.
The only other class it requires is `Chessboard`.

`GameStateChecker` maintains the game state.
It searches for checks, checkmate, stalemate.
To find checks, it requires the `Chessboard`.
To find stalemate and checkmate, it needs to determine when a player has no legal moves.
So, this class also requires `MoveGenerator`.

`MoveGenerator` gives methods for generating legal moves.
Each move generated is represented by a `Move` object, which contains all the information
required for making and undoing the move (starting and ending tiles, pieces involved).
It contains the logic for piece movement and legality checks.
To check for legality, it needs to check for checks using `GameStateChecker`.
For move generation, it requires the `Chessboard` and the board state stored in `MoveMaker`.
This is because castling and en passant are state-based moves.


`generateLegalMoves()` needs `isCheck()`
`isMate()` needs `generateLegalMoves()`

# To test program:
(1) make
(2) ./chess-exec
(3) make clean

# Completed files
observer (no impl needed)
subject
window

Board Representation:
https://www.chessprogramming.org/Mailbox
https://www.chessprogramming.org/10x12_Board

Moves:
https://www.chessprogramming.org/Incremental_Updates
https://www.chessprogramming.org/Vector_Attacks
https://www.chessprogramming.org/Encoding_Moves (From-To Based)

Engine (if we add computer level 4):
https://www.chessprogramming.org/Depth-First
https://www.chessprogramming.org/Minimax
https://www.chessprogramming.org/Negamax
https://www.chessprogramming.org/Alpha-Beta

