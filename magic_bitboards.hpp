#include "sliding_piece_magics.hpp"

U64* rookMagicDB[64]; /* Lookup Table for rook attacks */
U64* bishopMagicDB[64]; /* Lookup Table for rook attacks */

U64 slowRookGeneration(int square, U64 blockers) {
    // Initialize rook moves for magic bitboard tables.
    // Generate moves for one move
    U64 moves = 0;
    U64 position;
    position = (U64)1 << square; /* Set position to starting square */
    // Ray South.
    while (position) {
        position <<= 8; /* Move down */
        moves |= position; /* Add position to moves */
        if (blockers & position) break; /* If blocker is present, break */
        if (position & ranksLookup[63]) break; /* If reached end of board, break */
    }
    position = (U64)1 << square; /* Set position to starting square */
    // Ray North
    while (position) {
        position >>= 8; /* Move up */
        moves |= position; /* Add position to moves */
        if (blockers & position) break; /* If blocker is present, break */
        if (position & ranksLookup[0]) break; /* If reached end of board, break */
    }
    position = (U64)1 << square; /* Set position to starting square */
    // Ray Left
    if (!(position & filesLookup[0])) { /* Check if nex move will overflow */
        while (position) {
            position >>= 1; /* Move left */
            moves |= position; /* Add position to moves */
            if (blockers & position) break; /* If blocker is present, break */
            if (position & filesLookup[0]) break; /* If reached end of board, break */
        }
    }
    position = (U64)1 << square; /* Set position to starting square */
    // Ray Right
    if (!(position & filesLookup[63])) { /* Check if nex move will overflow */
        while (position) {
            position <<= 1; /* Move right */
            moves |= position; /* Add position to moves */
            if (blockers & position) break; /* If blocker is present, break */
            if (position & filesLookup[63]) break; /* If reached end of board, break */
        }
    }
    return moves;
}

void initRookSquareDB(int square) {
    // Initialize rook attacks for a square.
    rookMagicDB[square] = (U64*)calloc(1,sizeof(U64)); /* Allocate memory for the attack table */
    int maxIndex = 0; /* Size of table */
    U64 mask = rookMaskLookup[square]; /* Mask of bits*/
    U64 occupancies = 0; /* Occupancy bits */
    U64 index; /* Index for moves.*/
    U64 magic = rookMagicLookup[square]; /* Magic number for square */
    int shift = rookShiftLookup[square]; /* Magic bitboard shift */
    do {
        U64 moves = slowRookGeneration(square, occupancies); /* Generate rook moves */
        index = occupancies * magic;
        index >>= shift; /* Shift product to calculate final index */
        if (index > maxIndex) { /* If the index is greater than the db size, */
            rookMagicDB[square] = (U64*)realloc(rookMagicDB[square], (index + 1) * sizeof(U64)); /* Reallocate memory to fit index. */
            maxIndex = index; /* Update max index */
        }
        std::cout << "\r" << "Occupancy bits: " << printAsBin(occupancies);
        rookMagicDB[square][index] = moves; /* Add / re-add moves to db */
        occupancies = (occupancies - mask) & mask; /* Move on to next set of occupancy bits. */
    }
    while (occupancies);
    std::cout << endl;
}

void initRookDB() {
    // Init rook attack table.
    for (size_t i = 0; i < 64; i++) /* For every square, */
    {
        std::cout << "Generating rook attack tables for square [" << i << "]" << endl;
        initRookSquareDB(i); /* Init Square DB*/
    }
    
}

void deleteRookDB() {
    // Delete rook square db.
    for (size_t i = 0; i < 64; i++)
    {
        free(rookMagicDB[i]);
    }
    
}

U64 getRookMoves(int square, U64 own, U64 opponent) {
    // Returns the possible moves for a certian rook.
    U64 occupancies; /* Will contain all occupancy bits */
    U64 moves; /* Will contain all moves for this rook */
    occupancies = own | opponent; /* Combine both team pieces for original blocker set */
    occupancies &= rookMaskLookup[square]; /* Filter out irrelevant blockers */
    occupancies *= rookMagicLookup[square]; /* Multiply by magic number */
    occupancies >>= rookShiftLookup[square]; /* Shift to get index */
    moves = rookMagicDB[square][occupancies]; /* Get attacks from magic attack table */
    moves &= ~own; /* Any moves blocked by own pieces */
    return moves;
}

U64 slowBishopGeneration(int square, U64 blockers) {
    // Initialize rook moves for magic bitboard tables.
    // Generate moves for one square
    U64 moves = 0;
    U64 position;
    position = (U64)1 << square; /* Set position to starting square */
    // Ray NorthEast
    if (!(filesLookup[63] & position)) {/* Check if next move will overflow */
        while (position) {
            position >>= 7; /* Move down and right */
            moves |= position; /* Add position to moves */
            if (blockers & position) break; /* If blocker is present, break */
            if (position & (filesLookup[63] | ranksLookup[0])) break; /* If reached end of board, break */
        }
    }
    position = (U64)1 << square; /* Set position to starting square */
    // Ray SouthEast
    if (!(filesLookup[63] & position)) {/* Check if next move will overflow */
        while (position) {
            position <<= 9; /* Move down and right */
            moves |= position; /* Add position to moves */
            if (blockers & position) break; /* If blocker is present, break */
            if (position & (filesLookup[63] | ranksLookup[63])) break; /* If reached end of board, break */
        }
    }
    position = (U64)1 << square; /* Set position to starting square */
    // Ray NorthWest
    if (!(filesLookup[0] & position)) {/* Check if next move will overflow */
        while (position) {
            position >>=9; /* Move down and right */
            moves |= position; /* Add position to moves */
            if (blockers & position) break; /* If blocker is present, break */
            if (position & (filesLookup[0] | ranksLookup[0])) break; /* If reached end of board, break */
        }
    }
    // Ray SouthWest
    position = (U64)1 << square; /* Set position to starting square */
    if (!(filesLookup[0] & position)) {/* Check if next move will overflow */
        while (position) {
            position <<= 7; /* Move down and right */
            moves |= position; /* Add position to moves */
            if (blockers & position) break; /* If blocker is present, break */
            if (position & (filesLookup[0] | ranksLookup[63])) break; /* If reached end of board, break */
        }
    }
    return moves;
}

void initBishopSquareDB(int square) {
    // Initialize bishop attacks for a square.
    bishopMagicDB[square] = (U64*)calloc(1,sizeof(U64)); /* Allocate memory for the attack table */
    int maxIndex = 0; /* Size of table */
    U64 mask = bishopMaskLookup[square]; /* Mask of bits*/
    U64 occupancies = 0; /* Occupancy bits */
    U64 index; /* Index for moves.*/
    U64 magic = bishopMagicLookup[square]; /* Magic number for square */
    int shift = bishopShiftLookup[square]; /* Magic bitboard shift */
    do {
        U64 moves = slowBishopGeneration(square, occupancies); /* Generate bishop moves */
        index = occupancies * magic;
        index >>= shift; /* Shift product to calculate final index */
        if (index > maxIndex) { /* If the index is greater than the db size, */
            bishopMagicDB[square] = (U64*)realloc(bishopMagicDB[square], (index + 1) * sizeof(U64)); /* Reallocate memory to fit index. */
            maxIndex = index; /* Update max index */
        }
        std::cout << "\r" << "Occupancy bits: " << printAsBin(occupancies);
        bishopMagicDB[square][index] = moves; /* Add / re-add moves to db */
        occupancies = (occupancies - mask) & mask; /* Move on to next set of occupancy bits. */
    }
    while (occupancies);
    std::cout << endl;
}

void initBishopDB() {
    // Init bishop attack table.
    for (size_t i = 0; i < 64; i++) /* For every square, */
    {
        std::cout << "Generating bishop attack tables for square [" << i << "]" << endl;
        initBishopSquareDB(i); /* Init Square DB*/
    }
    
}

void deleteBishopDB() {
    // Delete bishop square db.
    for (size_t i = 0; i < 64; i++)
    {
        free(bishopMagicDB[i]);
    }
    
}

U64 getBishopMoves(int square, U64 own, U64 opponent) {
    // Returns the possible moves for a certian bishop.
    U64 occupancies; /* Will contain all occupancy bits */
    U64 moves; /* Will contain all moves for this rook */
    occupancies = own | opponent; /* Combine both team pieces for original blocker set */
    occupancies &= bishopMaskLookup[square]; /* Filter out irrelevant blockers */
    occupancies *= bishopMagicLookup[square]; /* Multiply by magic number */
    occupancies >>= bishopShiftLookup[square]; /* Shift to get index */
    moves = bishopMagicDB[square][occupancies]; /* Get attacks from magic attack table */
    moves &= ~own; /* Any moves blocked by own pieces */
    return moves;
}