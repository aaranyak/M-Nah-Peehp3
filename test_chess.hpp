#include "search.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

int CountMoves(BitBoard board, int depth, bool team) {
    if (depth){
        Board renderer;
        vector<BitBoard> moves = generateMoves(board, team);
        int count = 0;
        for (auto &&position : moves)
        {
            if (!isCheck(position, team)) {
                count += CountMoves(position, depth - 1, !team);
            }
            else {
                std::cout << "Check!" << endl;
            }
        }
        return count;
    }
    else {
        return 1;
    }
}