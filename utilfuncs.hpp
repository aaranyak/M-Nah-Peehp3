#include "bitboards.hpp"
#include <assert.h>
void renderBoard(Board board) {
    // Prints out a simple representation of the board.
    BitBoard boardState = board.boardState;
    std::cout << "    h   g   f   e   d   c   b   a\n";
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
    for (size_t y = 0; y < 8; y++)
    {
        std::cout << y + 1 << " |";
        for (size_t x = 0; x < 8; x++)
        {
            char letter;
            U64 position = 0;
            position |= 1;
            position <<= ((8 * y) + x);
            if (boardState.bPawns & position) {
                letter = 'p';
            }
            else if (boardState.wPawns & position) {
                letter = 'P';
            }
            else if (boardState.bRooks & position) {
                letter = 'r';
            }                
            else if (boardState.wRooks & position) {
                letter = 'R';
            }
            else if (boardState.bKnights & position) {
                letter = 'n';
            }                
            else if (boardState.wKnights & position) {
                letter = 'N';
            }
            else if (boardState.bBishops & position) {
                letter = 'b';
            }                
            else if (boardState.wBishops & position) {
                letter = 'B';
            }
            else if (boardState.bKing & position) {
                letter = 'k';
            }                
            else if (boardState.wKing & position) {
                letter = 'K';
            }
            else if (boardState.bQueens & position) {
                letter = 'q';
            }                
            else if (boardState.wQueens & position) {
                letter = 'Q';
            }
            else {
                letter = ' ';
            }
            std::cout << " " << letter << " |";
        }
        std::cout << "\n";
        std::cout << "  +---+---+---+---+---+---+---+---+\n";
    }
}

U64 getTeamMask(BitBoard board, bool team) {
    // Returns a mask of all the pieces in a team.
    U64 mask = 0;
    if (team) {
        mask = board.wPawns | board.wRooks | board.wKnights | board.wBishops | board.wKing | board.wQueens;
    }
    else {
        mask = board.bPawns | board.bRooks | board.bKnights | board.bBishops | board.bKing | board.bQueens;
    }
    return mask;
}
const int bitScanIndex64[64] = {
    0, 47,  1, 56, 48, 27,  2, 60,
   57, 49, 41, 37, 28, 16,  3, 61,
   54, 58, 35, 52, 50, 42, 21, 44,
   38, 32, 29, 23, 17, 11,  4, 62,
   46, 55, 26, 59, 40, 36, 15, 53,
   34, 51, 20, 43, 31, 22, 10, 45,
   25, 39, 14, 33, 19, 30,  9, 24,
   13, 18,  8, 12,  7,  6,  5, 63
};
int bitScanForward(U64 bb) { /* Returns the index of the least significant bit */
   const U64 debruijn64 = 0x03f79d71b4cb0a89;
   assert(bb != 0);
   return bitScanIndex64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

BitBoard playMoveOnBoardByIndex(BitBoard *board, int start, int end) {
    int startP = (U64)1 << start;
    int endP = (U64)1 << end;
    checkForAttacks(board, endP, getTeamMask(*board, true) & startP);
    if (startP & board->wPawns) {
        board->wPawns ^= (endP | startP);
    }
    if (startP & board->wRooks) {
        board->wRooks ^= (endP | startP);
    }
    if (startP & board->wKnights) {
        board->wKnights ^= (endP | startP);
    }
    if (startP & board->wBishops) {
        board->wBishops ^= (endP | startP);        
    }
    if (startP & board->wQueens) {
        board->wQueens ^= (endP | startP);        
    }
    if (startP & board->wKing) {
        board->wKing ^= (endP | startP);        
    }

    if (startP & board->bPawns) {
        board->bPawns ^= (endP | startP);
    }
    if (startP & board->bRooks) {
        board->bRooks ^= (endP | startP);
    }
    if (startP & board->bKnights) {
        board->bKnights ^= (endP | startP);
    }
    if (startP & board->bBishops) {
        board->bBishops ^= (endP | startP);        
    }
    if (startP & board->bQueens) {
        board->bQueens ^= (endP | startP);        
    }
    if (startP & board->bKing) {
        board->bKing ^= (endP | startP);        
    }
}

void renderBitBoard(U64 bitBoard) {
    // Prints out a simple representation of the U64 int.
    std::cout << "    h   g   f   e   d   c   b   a\n";
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
    for (size_t y = 0; y < 8; y++)
    {
        std::cout << y + 1 << " |";
        for (size_t x = 0; x < 8; x++)
        {
            char letter = ' ';
            U64 position = 0;
            position |= 1;
            position <<= ((8 * y) + x);
            if (position & bitBoard) {
                letter = '1';
            }
            std::cout << " " << letter << " |";
        }
        std::cout << "\n";
        std::cout << "  +---+---+---+---+---+---+---+---+\n";
    }
}

void renderBoardArray(auto array[64]) {
    // Prints out a simple representation of an array..
    std::cout << "    h   g   f   e   d   c   b   a\n";
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
    for (size_t y = 0; y < 8; y++)
    {
        std::cout << y + 1 << " |";
        for (size_t x = 0; x < 8; x++)
        {
            int position = 0;
            position = ((8 * y) + x);
            std::cout << " " << array[position] << " |";
        }
        std::cout << "\n";
        std::cout << "  +---+---+---+---+---+---+---+---+\n";
    }
}