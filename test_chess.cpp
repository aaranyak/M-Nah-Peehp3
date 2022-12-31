#include "generate_moves.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
class TestChess {
    Board board;
    bool turn;
    public:
        TestChess(bool turn) {
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
            this->board.initBoardState(boardInitState);
        };
        void play() {
            while (true) {
                renderBoard(this->board);
                string input = "";
                std::cout << "Play Move: ";
                std::cin >> input;
                if (input == "q") {
                    break;
                }
                else {
                    std::string inString;
                    std::cout << "Play Move: "
                    std::cin >> inString;
                    int startP = inString
                }
            }
        }
};

int main(int argc, char const *argv[])
{
    // TestChess testChess = new TestChess(true);
    // testChess.play();
    std::string thisIN;
    std::cin >> thisIN;
    return 0;
}
