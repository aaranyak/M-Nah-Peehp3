#include <iostream>
#include "test_chess.hpp"
#include <chrono>
#include <vector>
using namespace std::chrono;
int main(int argc, char *argv[])
{
    char boardInitState[64]  = {    
        'R','N','B','K','Q','B','N','R',
        'P','P','P','P','P','P','P','P',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        'p','p','p','p','p','p','p','p',
        'r','n','b','k','q','b','n','r'
    };
    Board board;
    board.initBoardState(boardInitState);
    initRookDB();
    system("clear");
    vector<BitBoard> moves = generateMoves(board.boardState, true);
    generate_sliding_piece_masks();
    deleteRookDB();
}