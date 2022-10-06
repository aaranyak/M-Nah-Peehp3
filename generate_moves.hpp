#include <vector>
#include "jumping_piece_moves.hpp"
using namespace std;
vector<BitBoard> generateMoves(BitBoard board, bool team) {
    // Generates all the possible resulting board states from a current board state.
    return {};
}
vector<BitBoard> generateKnightMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving the knight.
    vector<BitBoard> retVal  {};
    if (team) { /* by moving the white knight */
        U64 ownTeamMask = getTeamMask(board, team); /* The opponent team's mask */
        U64 lastValue = board.wKnights; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int knightPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 knightMoves = getKnightMask(knightPosition); /* Get the pattern of moves for the knight */
            knightMoves &= ~ownTeamMask; /* Remove the blocked squares from the mask */
            while (knightMoves) { /* While there are moves left */
                U64 move = knightMoves & -knightMoves; /* Isolate next move */
                BitBoard newBoard; /* Create the new board */
                copyBitBoard(&newBoard, board); /* Make the bitboard same as the board */
                newBoard.wKnights ^= move | isolatedLSB; /* Move the knight */
                checkForAttacks(&newBoard, move, team); /* Check for captures */
                retVal.push_back(newBoard); /* Add the new board to list */
                knightMoves &= ~move; /* Update the remaining moves */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    else { /* by moving the black knight */
        U64 ownTeamMask = getTeamMask(board, team); /* The opponent team's mask */
        U64 lastValue = board.bKnights; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int knightPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 knightMoves = getKnightMask(knightPosition); /* Get the pattern of moves for the knight */
            knightMoves &= ~ownTeamMask; /* Remove the blocked squares from the mask */
            while (knightMoves) { /* While there are moves left */
                U64 move = knightMoves & -knightMoves; /* Isolate next move */
                BitBoard newBoard; /* Create the new board */
                copyBitBoard(&newBoard, board);
                newBoard.bKnights ^= move | isolatedLSB;
                checkForAttacks(&newBoard, move, team); /* Check for captures */
                retVal.push_back(newBoard); /* Add the new board to list */
                knightMoves &= ~move; /* Update the remaining moves */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    return retVal; /* Return the generated moves */
}