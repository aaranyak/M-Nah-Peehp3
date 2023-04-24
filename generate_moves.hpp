#include <vector>
#include "magic_bitboards.hpp"
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

vector<BitBoard> pawnPromotion(BitBoard board, bool team, U64 piece) {
    // Generate Pawn Promotion Moves
    BitBoard queenBoard; /* Board for promoting to queen */
    BitBoard rookBoard; /* Board for promoting rook*/
    BitBoard bishopBoard; /* Board for promoting bishop*/
    BitBoard knightBoard; /* Board for promoting knight*/
    // Copy board data to bitboard
    copyBitBoard(&queenBoard, board);
    copyBitBoard(&rookBoard, board);
    copyBitBoard(&bishopBoard, board);
    copyBitBoard(&knightBoard, board);
    // If white is playing
    if (team) {
        // Promote Queen
        queenBoard.wPawns &= ~piece; /* Remove Pawn */
        queenBoard.wQueens |= piece; /* Add Queen */
        // Promote Rook
        rookBoard.wPawns &= ~piece; /* Remove Pawn */
        rookBoard.wRooks |= piece; /* Add Rook */
        // Promote Bishop
        bishopBoard.wPawns &= ~piece; /* Remove Pawn */
        bishopBoard.wBishops |= piece; /* Add Bishop */
        // Promote Knight
        knightBoard.wPawns &= ~piece; /* Remove Pawn */
        knightBoard.wKnights |= piece; /* Add Knight */
    }
    // If black is playing
    else {
        // Promote Queen
        queenBoard.bPawns &= ~piece; /* Remove Pawn */
        queenBoard.bQueens |= piece; /* Add Queen */
        // Promote Rook
        rookBoard.bPawns &= ~piece; /* Remove Pawn */
        rookBoard.bRooks |= piece; /* Add Rook */
        // Promote Bishop
        bishopBoard.bPawns &= ~piece; /* Remove Pawn */
        bishopBoard.bBishops |= piece; /* Add Bishop */
        // Promote Knight
        knightBoard.bPawns &= ~piece; /* Remove Pawn */
        knightBoard.bKnights |= piece; /* Add Knight */
    }
    vector<BitBoard> promotions = {queenBoard, rookBoard, bishopBoard, knightBoard};
    return promotions;
}

vector<BitBoard> generatePawnMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving the pawns.
    U64 ownTeamMask = getTeamMask(board, team); /* Our own team mask*/
    U64 opponentTeamMask = getTeamMask(board, !team); /* The opponent team's mask */
    vector<BitBoard> retVal  {};
    if (team) { /* By moving the white pawns */
        U64 lastValue = board.wPawns; /* The remaining bits to be scanned */
        while (lastValue) /* While there are bits still remaining*/
        {
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            U64 pawnMoves = 0; /* Moves to play */

            // Add the pawn pattern to the moves to play
            pawnMoves |= (isolatedLSB << 8) /* Pawn moves forward*/
                & ~(ownTeamMask | opponentTeamMask); /* Check if square is blocked by any team */
            pawnMoves |= ((isolatedLSB << 16) & ranksLookup[24]) /* Double pawn push if pawn not yet moved*/
                & ~(ownTeamMask | opponentTeamMask) /* If square is not blocked*/
                & ~((ownTeamMask | opponentTeamMask) << 8); /* Make sure pawn cannot jump over other piece */
            pawnMoves |= ((isolatedLSB << 9) & ~filesLookup[0]) & opponentTeamMask; /* Check for attacks */
            pawnMoves |= ((isolatedLSB << 7) & ~filesLookup[7]) & opponentTeamMask; /* Check for attacks */
            while (pawnMoves) { /* While there are moves left */
                U64 move = pawnMoves & -pawnMoves; /* Isolate next move */
                BitBoard newBoard; /* Create the new board */
                copyBitBoard(&newBoard, board);
                newBoard.wPawns ^= move | isolatedLSB;
                checkForAttacks(&newBoard, move, team); /* Check for captures */
                retVal.push_back(newBoard); /* Add the new board to list */
                pawnMoves &= ~move; /* Update the remaining moves */
            }
            lastValue &= ~isolatedLSB; /* Update remaining pieces */
            // Check for pawn promotion
            U64 forward_move = (isolatedLSB << 8) & ~(ownTeamMask | opponentTeamMask); /* Pawn Forward Move */
            if (forward_move & ranksLookup[57]) { /* If pawn is on last square */
                BitBoard movedPawn; /* Create new board */
                copyBitBoard(&movedPawn, board); /* Copy data to new board */
                movedPawn.wPawns ^= forward_move | isolatedLSB; /* Move Pawn */
                vector<BitBoard> pawnPromotions = pawnPromotion(movedPawn, team, forward_move); /* Create Promotion Options */
                retVal.insert(retVal.end(), pawnPromotions.begin(), pawnPromotions.end()); /* Add them to list */
            }
        }
        
    }
    else { /* By moving the black pawns */
        U64 lastValue = board.bPawns; /* The remaining bits to be scanned */
        while (lastValue) /* While there are bits still remaining*/
        {
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            U64 pawnMoves = 0; /* Moves to play */

            // Add the pawn pattern to the moves to play
            pawnMoves |= (isolatedLSB >> 8) /* Pawn moves forward*/
                & ~(ownTeamMask | opponentTeamMask); /* Check if square is blocked by any team */
            pawnMoves |= ((isolatedLSB >> 16) & ranksLookup[32]) /* Double pawn push if pawn not yet moved*/
                & ~(ownTeamMask | opponentTeamMask) /* If square is not blocked*/
                & ~((ownTeamMask | opponentTeamMask) >> 8); /* Make sure pawn cannot jump over other piece */
            pawnMoves |= ((isolatedLSB >> 9) & ~filesLookup[0]) & opponentTeamMask; /* Check for attacks */
            pawnMoves |= ((isolatedLSB >> 7) & ~filesLookup[7]) & opponentTeamMask; /* Check for attacks */
            
            while (pawnMoves) { /* While there are moves left */
                U64 move = pawnMoves & -pawnMoves; /* Isolate next move */
                BitBoard newBoard; /* Create the new board */
                copyBitBoard(&newBoard, board);
                newBoard.bPawns ^= move | isolatedLSB;
                checkForAttacks(&newBoard, move, team); /* Check for captures */
                retVal.push_back(newBoard); /* Add the new board to list */
                pawnMoves &= ~move; /* Update the remaining moves */
            }
            lastValue &= ~isolatedLSB; /* Update remaining pieces */
            // Check for pawn promotion
            U64 forward_move = (isolatedLSB >> 8) & ~(ownTeamMask | opponentTeamMask); /* Pawn Forward Move */
            if (forward_move & ranksLookup[0]) { /* If pawn is on last square */
                BitBoard movedPawn; /* Create new board */
                copyBitBoard(&movedPawn, board); /* Copy data to new board */
                movedPawn.bPawns ^= forward_move | isolatedLSB; /* Move Pawn */
                vector<BitBoard> pawnPromotions = pawnPromotion(movedPawn, team, forward_move); /* Create Promotion Options */
                retVal.insert(retVal.end(), pawnPromotions.begin(), pawnPromotions.end()); /* Add them to list */
            }
        }
        
    }
    return retVal;
}
vector<BitBoard> generateRookMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving rooks.
    vector<BitBoard> retVal  {};
    if (team) { /* by moving the white rook */
        U64 ownTeamMask = getTeamMask(board, team); /* Our Own Team mask */
        U64 opponentTeamMask = getTeamMask(board, !team); /* The Opponent Team mask */        
        U64 lastValue = board.wRooks; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int rookPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 moves = getRookMoves(rookPosition, ownTeamMask, opponentTeamMask); /* Get the rook attacks from the magic bitboard table */
            while (moves) { /* Loop through all the rook moves */
                U64 move = moves & -moves; /* Isolate the least significant bit */
                BitBoard newBoard; /* New board position for this move */
                copyBitBoard(&newBoard, board); /* Copy the old board position */
                newBoard.wRooks ^= move | isolatedLSB; /* Move the rook to new position */
                checkForAttacks(&newBoard, move, team); /* Capture piece on square if any */
                retVal.push_back(newBoard); /* Add move to return list */
                moves &= ~move; /* Reset LSB */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    else { /* By moving the white rook */
        U64 ownTeamMask = getTeamMask(board, team); /* Our Own Team mask */
        U64 opponentTeamMask = getTeamMask(board, !team); /* The Opponent Team mask */        
        U64 lastValue = board.bRooks; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int rookPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 moves = getRookMoves(rookPosition, ownTeamMask, opponentTeamMask); /* Get the rook attacks from the magic bitboard table */
            while (moves) { /* Loop through all the rook moves */
                U64 move = moves & -moves; /* Isolate the least significant bit */
                BitBoard newBoard; /* New board position for this move */
                copyBitBoard(&newBoard, board); /* Copy the old board position */
                newBoard.bRooks ^= move | isolatedLSB; /* Move the rook to new position */
                checkForAttacks(&newBoard, move, team); /* Capture piece on square if any */
                retVal.push_back(newBoard); /* Add move to return list */
                moves &= ~move; /* Reset LSB */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    return retVal; /* Return the generated moves */
}

vector<BitBoard> generateBishopMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving bishops.
    vector<BitBoard> retVal  {};
    if (team) { /* by moving the white bishop */
        U64 ownTeamMask = getTeamMask(board, team); /* Our Own Team mask */
        U64 opponentTeamMask = getTeamMask(board, !team); /* The Opponent Team mask */        
        U64 lastValue = board.wBishops; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int bishopPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 moves = getBishopMoves(bishopPosition, ownTeamMask, opponentTeamMask); /* Get the bishop attacks from the magic bitboard table */
            while (moves) { /* Loop through all the bishops moves */
                U64 move = moves & -moves; /* Isolate the least significant bit */
                BitBoard newBoard; /* New board position for this move */
                copyBitBoard(&newBoard, board); /* Copy the old board position */
                newBoard.wBishops ^= move | isolatedLSB; /* Move the bishops to new position */
                checkForAttacks(&newBoard, move, team); /* Capture piece on square if any */
                retVal.push_back(newBoard); /* Add move to return list */
                moves &= ~move; /* Reset LSB */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    else { /* by moving the black bishop */
        U64 ownTeamMask = getTeamMask(board, team); /* Our Own Team mask */
        U64 opponentTeamMask = getTeamMask(board, !team); /* The Opponent Team mask */        
        U64 lastValue = board.bBishops; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int bishopPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 moves = getBishopMoves(bishopPosition, ownTeamMask, opponentTeamMask); /* Get the bishop attacks from the magic bitboard table */
            while (moves) { /* Loop through all the bishops moves */
                U64 move = moves & -moves; /* Isolate the least significant bit */
                BitBoard newBoard; /* New board position for this move */
                copyBitBoard(&newBoard, board); /* Copy the old board position */
                newBoard.bBishops ^= move | isolatedLSB; /* Move the bishops to new position */
                checkForAttacks(&newBoard, move, team); /* Capture piece on square if any */
                retVal.push_back(newBoard); /* Add move to return list */
                moves &= ~move; /* Reset LSB */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    return retVal; /* Return the generated moves */
}

vector<BitBoard> generateQueenMoves(BitBoard board, bool team) {
    // Generates all the resulting board states by moving queens.
    vector<BitBoard> retVal  {};
    if (team) { /* by moving the white queen */
        U64 ownTeamMask = getTeamMask(board, team); /* Our Own Team mask */
        U64 opponentTeamMask = getTeamMask(board, !team); /* The Opponent Team mask */        
        U64 lastValue = board.wQueens; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int queenPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 rookMoves = getRookMoves(queenPosition, ownTeamMask, opponentTeamMask); /* Get the rook attacks from the magic bitboard table */
            U64 bishopMoves = getBishopMoves(queenPosition, ownTeamMask, opponentTeamMask); /* Get the bishop attacks from the magic bitboard table */
            U64 moves = rookMoves | bishopMoves;
            while (moves) { /* Loop through all the queen's moves */
                U64 move = moves & -moves; /* Isolate the least significant bit */
                BitBoard newBoard; /* New board position for this move */
                copyBitBoard(&newBoard, board); /* Copy the old board position */
                newBoard.wQueens ^= move | isolatedLSB; /* Move the queen to new position */
                checkForAttacks(&newBoard, move, team); /* Capture piece on square if any */
                retVal.push_back(newBoard); /* Add move to return list */
                moves &= ~move; /* Reset LSB */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    else { /* by moving the white queen */
        U64 ownTeamMask = getTeamMask(board, team); /* Our Own Team mask */
        U64 opponentTeamMask = getTeamMask(board, !team); /* The Opponent Team mask */        
        U64 lastValue = board.bQueens; /* The remaining bits to be scanned */
        while (lastValue) { /* While there are still bits remaining */
            U64 isolatedLSB = lastValue & -lastValue; /* Isolate the least significant bit */
            int queenPosition = bitScanForward(isolatedLSB); /* Get the index of the least significant bit */
            U64 rookMoves = getRookMoves(queenPosition, ownTeamMask, opponentTeamMask); /* Get the rook attacks from the magic bitboard table */
            U64 bishopMoves = getBishopMoves(queenPosition, ownTeamMask, opponentTeamMask); /* Get the bishop attacks from the magic bitboard table */
            U64 moves = rookMoves | bishopMoves;
            while (moves) { /* Loop through all the queen's moves */
                U64 move = moves & -moves; /* Isolate the least significant bit */
                BitBoard newBoard; /* New board position for this move */
                copyBitBoard(&newBoard, board); /* Copy the old board position */
                newBoard.bQueens ^= move | isolatedLSB; /* Move the queen to new position */
                checkForAttacks(&newBoard, move, team); /* Capture piece on square if any */
                retVal.push_back(newBoard); /* Add move to return list */
                moves &= ~move; /* Reset LSB */
            }
        lastValue &= ~isolatedLSB; /* Update the remaining pieces */
        }
    }
    return retVal;
}
vector<BitBoard> generateMoves(BitBoard board, bool team) {
    // Generates all the possible resulting board states from a current board state.
    vector<BitBoard> moves {};
    vector<BitBoard> knightMoves = generateKnightMoves(board, team);
    vector<BitBoard> kingMoves = generateKingMoves(board, team);
    vector<BitBoard> pawnMoves = generatePawnMoves(board, team);
    vector<BitBoard> rookMoves = generateRookMoves(board, team);
    vector<BitBoard> bishopMoves = generateBishopMoves(board, team);
    vector<BitBoard> queenMoves = generateQueenMoves(board, team);
    moves.insert(moves.end(), knightMoves.begin(), knightMoves.end());
    moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());
    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    moves.insert(moves.end(), queenMoves.begin(), queenMoves.end());
    return moves;
}