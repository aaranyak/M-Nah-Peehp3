#include "legality_test.hpp"

// Define material contstants
#define M_PAWN 1
#define M_BISHOP 3
#define M_KNIGHT 3
#define M_ROOK 5
#define M_QUEEN 9

int sparsePopCount(U64 bitBoard) {
    // Return number of pieces in a sparsely populated BitBoard
    U64 position = bitBoard;
    int count = 0;
    while (position) { /* Loop over all pieces */
        count++;
        position &= position - 1; /* Reset LSB */
    }
    return count;
}

int staticEval(BitBoard board, bool team) {
    // Return a score for the bitboard.
    int score = 0;
    if (team) { /* If white is playing */
        // Add score for white
        score += sparsePopCount(board.wPawns) * M_PAWN; /* Add M_PAWN for each pawn */
        score += sparsePopCount(board.wBishops) * M_BISHOP; /* Add M_BISHOP for each bishop */
        score += sparsePopCount(board.wKnights) * M_KNIGHT; /* for Knights */
        score += sparsePopCount(board.wRooks) * M_ROOK; /* Rooks */
        score += sparsePopCount(board.wQueens) * M_QUEEN; /* And Queens */
        // Subtract score for black
        score -= sparsePopCount(board.bPawns) * M_PAWN; /* Add M_PAWN for each pawn */
        score -= sparsePopCount(board.bBishops) * M_BISHOP; /* Add M_BISHOP for each bishop */
        score -= sparsePopCount(board.bKnights) * M_KNIGHT; /* for Knights */
        score -= sparsePopCount(board.bRooks) * M_ROOK; /* Rooks */
        score -= sparsePopCount(board.bQueens) * M_QUEEN; /* And Queens */
    }
    else { /* If black is playing */
        // Subtract score for white
        score -= sparsePopCount(board.wPawns) * M_PAWN; /* Add M_PAWN for each pawn */
        score -= sparsePopCount(board.wBishops) * M_BISHOP; /* Add M_BISHOP for each bishop */
        score -= sparsePopCount(board.wKnights) * M_KNIGHT; /* for Knights */
        score -= sparsePopCount(board.wRooks) * M_ROOK; /* Rooks */
        score -= sparsePopCount(board.wQueens) * M_QUEEN; /* And Queens */
        // Add score for black
        score += sparsePopCount(board.bPawns) * M_PAWN; /* Add M_PAWN for each pawn */
        score += sparsePopCount(board.bBishops) * M_BISHOP; /* Add M_BISHOP for each bishop */
        score += sparsePopCount(board.bKnights) * M_KNIGHT; /* for Knights */
        score += sparsePopCount(board.bRooks) * M_ROOK; /* Rooks */
        score += sparsePopCount(board.bQueens) * M_QUEEN; /* And Queens */
    }
    return score;
}

struct SearchResult {
    int score;
    BitBoard boardState;
};

SearchResult searchResult(int score, BitBoard boardState) {
    // Return searchResult with given parameters.
    SearchResult result;
    result.score = score;
    result.boardState = boardState;
    return result;
}