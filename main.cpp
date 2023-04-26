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
    initBishopDB();
    system("clear");
    auto start = high_resolution_clock::now();
    SearchResult move = Search(board.boardState, 8, true, N_INF, P_INF);
    auto stop = high_resolution_clock::now();
    board.boardState = move.boardState;
    renderBoard(board);
    std::cout << "With a score of: " << move.score << endl;
    std::cout << "Took " << duration_cast<seconds>(stop - start).count() << " seconds to search a depth of 8." << endl;
    deleteRookDB();
    deleteBishopDB();\
    return 0;
}