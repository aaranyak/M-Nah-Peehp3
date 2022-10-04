#include <iostream>
#include "simple_utils.hpp"
using namespace std;

// The basic structure of a bitboard that we will use to represent a board.
struct BitBoard {
    // White piece bitboards.
    U64 wPawns = 0;
    U64 wRooks = 0;
    U64 wKnights = 0;
    U64 wBishops = 0;
    U64 wQueens = 0;
    U64 wKing = 0;
    // Black piece bitboards.
    U64 bPawns = 0;
    U64 bRooks = 0;
    U64 bKnights = 0;
    U64 bBishops = 0;
    U64 bQueens = 0;
    U64 bKing = 0;
    // Castling Eligibility
};

class Board 
{
public:
    Board() {
        // Class Constructor.
    }
    BitBoard boardState; // The board state.
    void initBoardState(char initState[64]) {
        for (size_t i = 64; i > 0; i--)
        {
            this->boardState.bPawns <<= 1;
            this->boardState.wPawns <<= 1;
            this->boardState.bRooks <<= 1;
            this->boardState.wRooks <<= 1;
            this->boardState.bKnights <<= 1;
            this->boardState.wKnights <<= 1;
            this->boardState.bBishops <<= 1;
            this->boardState.wBishops <<= 1;
            this->boardState.bKing <<= 1;
            this->boardState.wKing <<= 1;
            this->boardState.bQueens <<= 1;
            this->boardState.wQueens <<= 1;
            
            if (initState[i-1] == 'p') {
               this->boardState.bPawns |= 1;
            }
            if (initState[i-1] == 'P') {
               this->boardState.wPawns |= 1;
            }
            if (initState[i-1] == 'r') {
               this->boardState.bRooks |= 1;
            }
            if (initState[i-1] == 'R') {
               this->boardState.wRooks |= 1;
            }
            if (initState[i-1] == 'n') {
               this->boardState.bKnights |= 1;
            }
            if (initState[i-1] == 'N') {
               this->boardState.wKnights |= 1;
            }
            if (initState[i-1] == 'k') {
               this->boardState.bKing |= 1;
            }
            if (initState[i-1] == 'K') {
               this->boardState.wKing |= 1;
            }
            if (initState[i-1] == 'q') {
               this->boardState.bQueens |= 1;
            }
            if (initState[i-1] == 'Q') {
               this->boardState.wQueens |= 1;
            }
            if (initState[i-1] == 'b') {
               this->boardState.bBishops |= 1;
            }
            if (initState[i-1] == 'B') {
               this->boardState.wBishops |= 1;
            }
        }
        
    }
};

