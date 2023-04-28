#include "chess_functions.hpp"
#include <limits>
#include <algorithm>
#define P_INF 2147483647 /* Positive Infinity */
#define N_INF -2147483647 /* Negative Infinity */
#define BB_0 emptyBoard
BitBoard emptyBoard;
int depth = 0;
SearchResult PlainSearch(BitBoard board, int depth, bool team) {
    // Plain MinMax Search implementation.
    if (depth) { /* If depth has not reached zero */
        vector<BitBoard> pseudoLegalMoves = generateMoves(board, team); /* Generate all pseudo legal moves */
        vector<BitBoard> legalMoves;
        std::copy_if(pseudoLegalMoves.begin(), pseudoLegalMoves.end(), std::back_inserter(legalMoves), [team](BitBoard &board) { /* Copy only legal moves to the second list */
            return !isCheck(board, team); /* Only copy if board state is not check */
        });
        if (legalMoves.size()) { /* If not checkmate / stalemate */
            SearchResult maxResult = searchResult(N_INF, BB_0); /* Maximum result will originally be negative infinity */
            for (auto &&boardPosition : legalMoves) /* Loop through all legal moves */
            {
                SearchResult result = PlainSearch(boardPosition, depth - 1, !team); /* Recursive call to the same function for next branch */
                result.score *= -1; /* Make the score negative, since it is from the other team's perspective */
                if (result.score >= maxResult.score) { /* If this value is greater than the older maximum result, */
                    maxResult = searchResult(result.score, boardPosition);  /* Update maximum result */
                }
            }
            return maxResult;
        }
        else { /* If checkmate / stalemate */
            if (isCheck(board, team)) { /* Checkmate !*/
                return searchResult(
                    N_INF, /* Return Negative Infinity */
                    BB_0
                );
            }
            else { /* Stalemate */
                return searchResult(0, BB_0); /* Return 0 */
            }
        }
    }
    else { /* If at end of search */
        return searchResult(
            staticEval(board, team), /* Return static evaluation */
            BB_0
        );
    }
}

SearchResult Search(BitBoard board, int depth, bool team, int alpha, int beta) {
    //  MinMax Search implementation with alpha-beta pruning.
    if (depth) { /* If depth has not reached zero */
        vector<BitBoard> pseudoLegalMoves = generateMoves(board, team); /* Generate all pseudo legal moves */
        vector<BitBoard> legalMoves;
        std::copy_if(pseudoLegalMoves.begin(), pseudoLegalMoves.end(), std::back_inserter(legalMoves), [team](BitBoard &board) { /* Copy only legal moves to the second list */
            return !isCheck(board, team); /* Only copy if board state is not check */
        });
        if (legalMoves.size()) { /* If not checkmate / stalemate */
            SearchResult maxResult = searchResult(N_INF, legalMoves[0]); /* Maximum result will originally be negative infinity */
            for (auto &&boardPosition : legalMoves) /* Loop through all legal moves */
            {
                SearchResult result = Search(boardPosition, depth - 1, !team, -beta, -alpha); /* Recursive call to the same function for next branch */
                result.score *= -1; /* Make the score negative, since it is from the other team's perspective */
                if (result.score > maxResult.score) { /* If this value is greater than the older maximum result, */
                    maxResult = searchResult(result.score, boardPosition);  /* Update maximum result */
                }
                if (result.score > beta) { /* If current move is better than last best move */
                    return searchResult(beta, BB_0); /* Stop searching */
                }
                else {
                    alpha = max(alpha, result.score);
                }
            }
            return maxResult;
        }
        else { /* If checkmate / stalemate */
            if (isCheck(board, team)) { /* Checkmate !*/
                return searchResult(
                    N_INF, /* Return Negative Infinity */
                    BB_0
                );
            }
            else { /* Stalemate */
                return searchResult(0, BB_0); /* Return 0 */
            }
        }
    }
    else { /* If at end of search */
        depth = 0;
        return searchResult(
            staticEval(board, team),
            BB_0
        );
    }
}