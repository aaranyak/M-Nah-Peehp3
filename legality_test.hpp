#include "generate_moves.hpp"

U64 getKnightAttacks(U64 knights) {
    // Get the knight attack mask for the legality test.
    U64 positions = knights; /* Copy knights table */
    U64 finalAttackMask = 0;
    while (positions) { /* Loop through all the knights */
        U64 knight = positions & -positions; /* Isolate the least significant knight*/
        finalAttackMask |= getKnightMask(bitScanForward(knight)); /* Get the knight mask and add it to the bitboard */
        positions ^= knight; /* Reset LSB */
    }
    return finalAttackMask;
}

U64 getKingAttacks(U64 king) {
    // Get the knight attack mask for the legality test.
    U64 positions = king; /* Copy knights table */
    U64 finalAttackMask = 0;
    finalAttackMask |= getKingMask(bitScanForward(king)); /* Get the knight mask and add it to the bitboard */
    positions ^= king; /* Reset LSB */
    return finalAttackMask;
}
U64 getPawnAttacks(U64 pawns, bool team) {
    // Get pawn attack mask for legality test
    U64 finalAttackMask = 0;
    if (team) { /* If White is playing */
        finalAttackMask |= (pawns << 9) & ~(filesLookup[0]); /* Attack Southeast */
        finalAttackMask |= (pawns << 7) & ~(filesLookup[63]); /* Attack Southwest */
    }
    else { /* If Black is playing */
        finalAttackMask |= (pawns >> 9) & ~(filesLookup[63]); /* Attack Northwest */
        finalAttackMask |= (pawns >> 7) & ~(filesLookup[0]); /* Attack Northeast */
    }
    return finalAttackMask;
}

U64 getRookAttacks(BitBoard board, bool team) {
    // Get all rook attack positions.
    U64 own = getTeamMask(board, team);
    U64 opponent = getTeamMask(board, !team);
    U64 finalAttackMask = 0;
    if (team) {
        U64 position = board.wRooks; /* Rook positons */
        while (position) { /* Loop over all rooks */
            U64 rook = position & -position; /* Isolate LSB */
            finalAttackMask |= getRookMoves(bitScanForward(rook), own, opponent); /* Get rook moves from magic attack table */
            position ^= rook; /* Reset LSB */
        }
    }
    else {
        U64 position = board.bRooks; /* Rook positons */
        while (position) { /* Loop over all rooks */
            U64 rook = position & -position; /* Isolate LSB */
            finalAttackMask |= getRookMoves(bitScanForward(rook), own, opponent); /* Get rook moves from magic attack table */
            position ^= rook; /* Reset LSB */
        }
    }
    return finalAttackMask;
}

U64 getBishopAttacks(BitBoard board, bool team) {
    // Get all bishop attack positions.
    U64 own = getTeamMask(board, team);
    U64 opponent = getTeamMask(board, !team);
    U64 finalAttackMask = 0;
    if (team) {
        U64 position = board.wBishops; /* Bishop positons */
        while (position) { /* Loop over all bishops */
            U64 bishop = position & -position; /* Isolate LSB */
            finalAttackMask |= getBishopMoves(bitScanForward(bishop), own, opponent); /* Get bishop moves from magic attack table */
            position ^= bishop; /* Reset LSB */
        }
    }
    else {
        U64 position = board.bBishops; /* Bishop positons */
        while (position) { /* Loop over all bishops */
            U64 bishop = position & -position; /* Isolate LSB */
            finalAttackMask |= getBishopMoves(bitScanForward(bishop), own, opponent); /* Get bishop moves from magic attack table */
            position ^= bishop; /* Reset LSB */
        }
    }
    return finalAttackMask;
}

U64 getQueenAttacks(BitBoard board, bool team) {
    // Get all queen attack positions.
    U64 own = getTeamMask(board, team);
    U64 opponent = getTeamMask(board, !team);
    U64 finalAttackMask = 0;
    if (team) {
        U64 position = board.wQueens; /* Queen positons */
        while (position) { /* Loop over all Queens */
            U64 queen = position & -position; /* Isolate LSB */
            finalAttackMask |= getBishopMoves(bitScanForward(queen), own, opponent); /* Get queen moves from magic attack table */
            finalAttackMask |= getRookMoves(bitScanForward(queen), own, opponent); /* Get queen moves from magic attack table */
            position ^= queen; /* Reset LSB */
        }
    }
    else {
        U64 position = board.bQueens; /* Queen positons */
        while (position) { /* Loop over all queens */
            U64 queen = position & -position; /* Isolate LSB */
            finalAttackMask |= getBishopMoves(bitScanForward(queen), own, opponent); /* Get queen moves from magic attack table */
            finalAttackMask |= getRookMoves(bitScanForward(queen), own, opponent); /* Get queen moves from magic attack table */
            position ^= queen; /* Reset LSB */
        }
    }
    return finalAttackMask;
}

bool isCheck(BitBoard board, bool team) {
    // Detect if king of a certian colour is under check.
    U64 attackMask = 0; /* Attack mask of opponent team */
    if (team) { /* Detection for white */
        attackMask |= getKnightAttacks(board.bKnights); /* Add the attacks of the knights */
        attackMask |= getKingAttacks(board.bKing); /* Add the attacks of the king */
        attackMask |= getPawnAttacks(board.bPawns, !team); /* Add the attacks of the pawns */
        attackMask |= getRookAttacks(board, !team); /* Add the attacks of the rooks */
        attackMask |= getQueenAttacks(board, !team); /* Add the attacks of the queens */
        attackMask |= getBishopAttacks(board, !team); /* Add the attacks of the bishops */
        if (board.wKing & attackMask) { /* If the king is attacked by an enemy piece */
            return true;
        }
    }
    else {
        attackMask |= getKnightAttacks(board.wKnights); /* Add the attacks of the knights */
        attackMask |= getKingAttacks(board.wKing); /* Add the attacks of the king */
        attackMask |= getPawnAttacks(board.wPawns, !team); /* Add the attacks of the pawns */
        attackMask |= getRookAttacks(board, !team); /* Add the attacks of the rooks */
        attackMask |= getQueenAttacks(board, !team); /* Add the attacks of the queens */
        attackMask |= getBishopAttacks(board, !team); /* Add the attacks of the bishops */
        if (board.bKing & attackMask) { /* If the king is attacked by an enemy piece */
            return true;
        }
    }
    return false;
}