#include "generate_moves.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

int CountMoves(BitBoard board, int depth, bool team) {
    if (depth){
        vector<BitBoard> moves = generateMoves(board, team);
        int count = 0;
        for (auto &&position : moves)
        {
            count += CountMoves(position, depth - 1, !team);
        }
        return count;
    }
    else {
        return 1;
    }
}