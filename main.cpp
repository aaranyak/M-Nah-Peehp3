#include <iostream>
#include "generate_moves.hpp"
#include <chrono>
#include <vector>
using namespace std::chrono;

int main(int argc, char *argv[])
{
    char boardInitState[64]  = {    
        'R','N','B','K','Q','B','N','R',
        'P','P','P','P','P','P','P','P',
        ' ','p',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ','p','p','p','p','p','p','p',
        'r','n','b','k','q','b','n','r'
    };
    Board board;
    board.initBoardState(boardInitState);
    vector<BitBoard> moves = generatePawnMoves(board.boardState, true);
    for (size_t i = 0; i < moves.size(); i++)
    {
        board.boardState = moves[i];
        renderBoard(board);
        printf("\n\n");
    }
    std::cout << moves.size() << endl;
    return 0;
}