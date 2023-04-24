#include "generate_moves.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

U64 cover = 0;
void generate_sliding_piece_masks() {
    std::cout << "U64 rookMaskLookup[64] = {" << endl;
    for (size_t i = 0; i < 64; i++)
    {
        cover = 0;
        U64 position = 1;
        position <<= i;
        if (!(position & filesLookup[0])) {
            cover |= filesLookup[0];
        }
        if (!(position & filesLookup[63])) {
            cover |= filesLookup[63];
        }
        if (!(position & ranksLookup[0])) {
            cover |= ranksLookup[0];
        }
        if (!(position & ranksLookup[63])) {
            cover |= ranksLookup[63];
        }
        U64 pattern = filesLookup[i] | ranksLookup[i];
        pattern &= ~cover;
        pattern &= ~position;
        std::cout << "    " << pattern << "," << endl;
    }
    std::cout << "};" << endl;
    
}
