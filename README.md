
# Chess Engine
This is a simple chess engine written entirely in C. It uses a bitboard representation for efficient calculations. 

The program runs in the terminal and displays the board textually. There are two types of commands that can be
run while playing:

#### Movement commands
e.g. `E2E4` or `e2e4`

This will move a piece from square `E2` to square `E4` if it is a legal move.

#### The show command
e.g. `s E2`

This will display all legal moves a piece can make. For example, if a pawn is on `E2`, and there are no pawns
on `D3` or `F3`, the command will display `1. E3 2. E4`.

## TODO
The following are features that need to be implemented:

- En passant
- Check
- Checkmate
- Stalemate
- Castling

The following are features that *could* be implemented:

- Board/position scoring
- A bot to play against

## Author
Cole Carley

