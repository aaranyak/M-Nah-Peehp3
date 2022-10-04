#include "utilfuncs.hpp"
#include <vector>

vector<BitBoard> generateMoves(BitBoard board, bool team) {
    
    return {};
}
vector<BitBoard> generateKnightMoves(BitBoard board, bool team) {
    if (team) {
        U64 lastValue = board.wKnights;
        while (lastValue) {
            U64 isolatedLSB = lastValue & -lastValue;
            std::cout << bitScanForward(isolatedLSB) << std::endl;
            lastValue &= ~isolatedLSB;
        }
    }
    return {};
}