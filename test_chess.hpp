#include "generate_moves.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

int Search(int depth, BitBoard board, bool team) {
    if (depth) {
        int count = 0;
        vector<BitBoard> moves = generateMoves(board, team);
        for (auto &&bitboard : moves)
        {
            count += Search(depth - 1, bitboard, !team);
        }
        return count;
    }
    else {
        return 1;
    }
}
