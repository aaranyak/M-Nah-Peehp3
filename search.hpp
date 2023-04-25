#include "chess_functions.hpp"
#include <limits>
#include <algorithm>
#define P_INF std::numerical_limits<int>::max() /* Positive Infinity */
#define N_INF std::numeric_limits<int>::min() /* Negative Infinity */

SearchResult PlainSearch(BitBoard board, int depth, bool team) {
    // Plain MinMax Search implementation.
    if (depth) { /* If depth has not reached zero */
        vector<BitBoard> pseudoLegalMoves = generateMoves(board, team); /* Generate all pseudo legal moves */
        vector<BitBoard> legalMoves;
        std::copy_if(pseudoLegalMoves.begin(), pseudoLegalMoves.end(), std::back_inserter(legalMoves), [team](int &board) { /* Copy only legal moves to the second list */
            return !isCheck(board, team); /* Only copy if board state is not check */
        });
        if (legalMoves.size()) { /* If not checkmate / stalemate */
            SearchResult maxResult = searchResult(NULL, N_INF); /* Maximum result will originally be negative infinity */
            for (auto &&boardPosition : legalMoves) /* Loop through all legal moves */
            {
                SearchResult result = PlainSearch(boardPosition, depth - 1, !team); /* Recursive call to the same function for next branch */
                result.score *= -1; /* Make the score negative, since it is from the other team's perspective */
                if (result.score >= maxResult.score) { /* If this value is greater than the older maximum result, */
                    maxResult = searchResult(boardPosition, result.score);  /* Update maximum result */
                }
            }
            return maxResult;
        }
        else { /* If checkmate / stalemate */
            if (isCheck(board, team)) { /* Checkmate !*/
                return searchResult(
                    N_INF, /* Return Negative Infinity */
                    NULL,
                );
            }
            else { /* Stalemate */
                return searchResult(0, NULL); /* Return 0 */
            }
        }
    }
    else { /* If at end of search */
        return searchResult(
            staticEval(board, team), /* Return static evaluation */
            NULL
        );
    }
}