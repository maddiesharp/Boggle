//
// Place Holder Copyright Header
//

#ifndef BOGGLE_SOLVER_HELPER_H
#define BOGGLE_SOLVER_HELPER_H

#include "BoggleSolver.h"


using namespace std;


/// <summary>
///    --------------------- Theory of Operation ---------------------
/// The inline functions below are used by the IndexSolver class to check
/// if adjacent nodes in the boggle table exist and are a valid node to
/// traverse to.
/// 
/// There are 3 different types of cases that can be checked.
/// 1. (literal edge case) : This case is used to identify the top, bottom,
/// left, and right boundaries of the board.It checks if the searching
/// indexes(row, column) are out - of - range by either being negative, or
/// beyond the size of the row in question.
/// 2. (edgier case) : This case is a specific edge case that allows for
/// asymetric boggle boards.It is a weird way to play boggle, but it
/// is allowed here as a feature.
/// 
/// Ex.Rows are not all the same size.
/// { {a, s, d, f    }},
/// { {a, e, o       }},
/// { {q, r, s, t    }},
/// { {m, a, d, z, f }}
/// 
/// 3. (visited nodes case) : Nodes that have already been visited in this search
/// of character combinations are not considered a valid node per the
/// rules of Boggle.
/// 
/// Each of the helper inline functions corresponds to one of the 8 relative
/// directions that can be checked from the current node.Below is a diagram
/// showing the relative node positions to the CURRENT node.
/// 
/// { { up_left   , up        , up_right     } },
/// { { left      , CURRENT   , right        } },
/// { { down_left , down      , down_right   } },
/// 
/// The functions marked as "inline" to allow for multiple threads 
/// to "access" them without worry.
/// 
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
/// <param name="row">row index of the current boggle board char node</param>
/// <param name="col">column index of the current boggle board char node</param>
/// <param name="board">reference to the full board of boggle characters</param>
/// <param name="validNodes">reference to a set where a valid node can be stored, if found</param>
/// <param name="visitedNodes">reference to a set of node characters already in the path, used to check node validity</param>
inline void checkNodeUp(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newRow{ (int)row - 1 };

    if (newRow >= 0) // (literal edge case) if not on the top edge of the board
    {
        if (board[newRow].size() > col) // (edgier case) if the above index even exists
        {
            auto temp{ make_pair(size_t(newRow), col) };
            if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
            {
                validNodes.insert(temp);
            }
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
inline void checkNodeUpRight(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newRow{ (int)row - 1 };
    const int newCol{ (int)col + 1 };

    if (newRow >= 0) // (literal edge case) if not on the top edge of the board
    {
        if (board[newRow].size() > newCol) // (edgier case) if the above index even exists
        {
            auto temp{ make_pair(size_t(newRow), newCol) };
            if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
            {
                validNodes.insert(temp);
            }
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
inline void checkNodeRight(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newCol{ (int)col + 1 };

    if (newCol < board[row].size()) // (literal edge case) if not on the right edge of the board
    {
        auto temp{ make_pair(size_t(row), newCol) };
        if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
        {
            validNodes.insert(temp);
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
inline void checkNodeUpLeft(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newRow{ (int)row - 1 };
    const int newCol{ (int)col - 1 };

    if ((newRow >= 0) && (newCol >= 0)) // (literal edge case) if not on the top/left edges of the board
    {
        if (board[newRow].size() > newCol) // (edgier case) if the above index even exists
        {
            auto temp{ make_pair(size_t(newRow), newCol) };
            if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
            {
                validNodes.insert(temp);
            }
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
inline void checkNodeDown(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newRow{ (int)row + 1 };

    if (newRow < board.size()) // (literal edge case) if not on the bottom edge of the board
    {
        if (board[newRow].size() > col) // (edgier case) if the below index even exists
        {
            auto temp{ make_pair(size_t(newRow), col) };
            if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
            {
                validNodes.insert(temp);
            }
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
inline void checkNodeDownRight(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newRow{ (int)row + 1 };
    const int newCol{ (int)col + 1 };

    if (newRow < board.size()) // (literal edge case) if not on the bottom edge of the board
    {
        if (board[newRow].size() > newCol) // (edgier case) if the below index even exists
        {
            auto temp{ make_pair(size_t(newRow), newCol) };
            if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes) if node hasn't been visited
            {
                validNodes.insert(temp);
            }
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// </summary>
inline void checkNodeDownLeft(size_t& row, size_t& col, const BoggleBoard& board, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newRow{ (int)row + 1 };
    const int newCol{ (int)col - 1 };

    if (newRow < board.size() && (newCol >= 0)) // (literal edge case) if not on the bottom/left edges of the board
    {
        if (board[newRow].size() > newCol) // (edgier case) if the below index even exists
        {
            auto temp{ make_pair(size_t(newRow), newCol) };
            if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
            {
                validNodes.insert(temp);
            }
        }
    }
}


/// <summary>
/// See Theory of Operation above for more details.
/// NOTE - ORDER OF IF BLOCKS MATTERS
/// 
/// This particular function does not need the const BoggleBoard&
/// </summary>
inline void checkNodeLeft(size_t& row, size_t& col, BoggleSolver::BoardNodes& validNodes, BoggleSolver::BoardNodes& visitedNodes)
{
    const int newCol{ (int)col - 1 };

    if (newCol >= 0) // (literal edge case) if not on the left edge of the board
    {
        auto temp{ make_pair(size_t(row), newCol) };
        if (visitedNodes.find(temp) == visitedNodes.end()) // (visited nodes case) if node hasn't been visited
        {
            validNodes.insert(temp);
        }
    }
}


#endif // BOGGLE_SOLVER_HELPER_H
