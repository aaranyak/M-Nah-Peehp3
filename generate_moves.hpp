#include <vector>
#include "jumping_piece_moves.hpp"
vector<BitBoard> generateMoves(BitBoard board, bool team) {
    // Generates all the possible resulting board states from a current board state.
    return {};
}
vector<BitBoard> generateKnightMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving the knight.
    if (team) { /* by moving the white knight */
        U64 ownTeamMask = getTeamMask(board, team); /* The opponent team's mask */
        U64 lastValue = board.wKnights; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int knightPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 knightMoves = getKnightMask(knightPosition); /* Get the pattern of moves for the knight */
            knightMoves &= ~ownTeamMask; /* Remove the blocked squares from the mask */
            
        }
    }
    return {};
}