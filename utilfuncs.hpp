#include "bitboards.hpp"
void renderBoard(Board board) {
    BitBoard boardState = board.boardState;
    std::cout << "+---+---+---+---+---+---+---+---+\n";
    for (size_t y = 0; y < 8; y++)
    {
        std::cout << "|   |   |   |   |   |   |   |   |\n";
        std::cout << "|";
        for (size_t x = 0; x < 8; x++)
        {
            char letter;
            U64 position = 0;
            position |= 1;
            position <<= 63 - ((8 * y) + x);
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
        std::cout << "|   |   |   |   |   |   |   |   |\n";
        std::cout << "+---+---+---+---+---+---+---+---+\n";
    }
}

U64 getTeamMask(BitBoard board, bool team) {
    U64 mask = 0;
    if (team) {
        mask = board.wPawns | board.wRooks | board.wKnights | board.wBishops | board.wKing | board.wQueens;
    }
    else {
        mask = board.bPawns | board.bRooks | board.bKnights | board.bBishops | board.bKing | board.bQueens;
    }
    return mask;
}