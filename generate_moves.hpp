#include "jumping_piece_moves.hpp"
#include <vector>
vector<BitBoard> generateKnightMoves(BitBoard board, bool team) {
    vector<BitBoard> moves {};
    if (team) {
        U64 whiteMask = getTeamMask(board, true);
        for (U64 i = 1; i < 64; i++)
        {
            U64 position = 1;
            position <<= i;
            position &= board.wKnights;
            if (position) {
                U64 knightMask = getKnightMask(i);
                knightMask &= ~whiteMask;
                size_t pos = 1;
                pos <<= 63;
                for (i; pos > 0; pos >>= 1)
                {
                    U64 move = pos & knightMask;
                    if (move) {
                        printAsBin(move);
                        BitBoard newBoard = board;
                        newBoard.wKnights ^= move | board.wKnights;
                        newBoard.bPawns &= ~pos;
                        newBoard.bRooks &= ~pos;
                        newBoard.bKnights &= ~pos;
                        newBoard.bBishops &= ~pos;
                        newBoard.bQueens &= ~pos;
                        moves.push_back(newBoard);
                    }
                }
            }
        }
        
    }
    return moves;
}
vector<BitBoard> generateMoves(BitBoard board, bool team) {
    return generateKnightMoves(board, team);
}