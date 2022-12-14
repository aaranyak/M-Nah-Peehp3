#include <vector>
#include "jumping_piece_moves.hpp"
using namespace std;
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

vector<BitBoard> generateKingMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving the king.
    vector<BitBoard> retVal  {};
    if (team) { /* by moving the white king */
        U64 ownTeamMask = getTeamMask(board, team); /* The opponent team's mask */
        U64 lastValue = board.wKing; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int kingPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 kingMoves = getKingMask(kingPosition); /* Get the pattern of moves for the king */
            kingMoves &= ~ownTeamMask; /* Remove the blocked squares from the mask */
            while (kingMoves) { /* While there are moves left */
                U64 move = kingMoves & -kingMoves; /* Isolate next move */
                BitBoard newBoard; /* Create the new board */
                copyBitBoard(&newBoard, board); /* Make the bitboard same as the board */
                newBoard.wKing ^= move | isolatedLSB; /* Move the king */
                checkForAttacks(&newBoard, move, team); /* Check for captures */
                retVal.push_back(newBoard); /* Add the new board to list */
                kingMoves &= ~move; /* Update the remaining moves */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    else { /* by moving the black king */
        U64 ownTeamMask = getTeamMask(board, team); /* The opponent team's mask */
        U64 lastValue = board.bKing; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int kingPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 kingMoves = getKingMask(kingPosition); /* Get the pattern of moves for the king */
            kingMoves &= ~ownTeamMask; /* Remove the blocked squares from the mask */
            while (kingMoves) { /* While there are moves left */
                U64 move = kingMoves & -kingMoves; /* Isolate next move */
                BitBoard newBoard; /* Create the new board */
                copyBitBoard(&newBoard, board);
                newBoard.bKing ^= move | isolatedLSB;
                checkForAttacks(&newBoard, move, team); /* Check for captures */
                retVal.push_back(newBoard); /* Add the new board to list */
                kingMoves &= ~move; /* Update the remaining moves */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    return retVal; /* Return the generated moves */
}
vector<BitBoard> generatePawnMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving the pawns.
    U64 ownTeamMask = getTeamMask(team); /* Our own team mask*/
    U64 opponentTeamMask = getTeamMask(!team); /* The opponent team's mask */
    vector<BitBoard> retVal = {};
    if (team) { /* By moving the white pawns */
        U64 lastValue = board.wPawns; /* The remaining bits to be scanned */
        while (lastValue) /* While there are bits still remaining*/
        {
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
        }
        
    }
}
vector<BitBoard> generateMoves(BitBoard board, bool team) {
    // Generates all the possible resulting board states from a current board state.
    vector<BitBoard> moves {};
    vector<BitBoard> knightMoves = generateKnightMoves(board, team);
    vector<BitBoard> kingMoves = generateKingMoves(board, team);
    moves.insert(moves.end(), knightMoves.begin(), knightMoves.end());
    moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());
    return moves;
}