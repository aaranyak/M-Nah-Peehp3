#include <iostream>
#include "generate_moves.hpp"
#include <chrono>
#include <vector>
using namespace std::chrono;

int main(int argc, char *argv[])
{
    char boardInitState[64]  = {    
        'R','N','B',' ','Q','B','N','R',
        'P','P','P','P','P','P','P','P',
        ' ',' ',' ','K',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',' ',' ',' ',
        'p','p','p','p','p','p','p','p',
        'r','n','b','k','q','b','n','r'
    };
    Board board;
    board.initBoardState(boardInitState);
    renderBoard(board);
    
}