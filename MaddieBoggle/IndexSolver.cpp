//
// Place Holder Copyright Header
//

#ifdef _DEBUG
#include <cassert>
#include <iostream>
#endif

#include "IndexSolver.h"
#include "IndexSolverHelper.h"


/// <summary>
/// 
/// </summary>
/// <param name="dictionary"></param>
/// <param name="board"></param>
IndexSolver::IndexSolver(shared_ptr<const Dictionary> dictionary, const BoggleBoard& board) :
    m_board(board),
    m_dictionary(dictionary),
    m_visitedNodes(),
    m_answers(),
    m_currentWord("")
{
    assert(m_dictionary);
}


/// <summary>
/// 
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
void IndexSolver::findWords(size_t row, size_t col)
{
    bool qCondition { false };              // Flag used to identify if a the Q_CONDITION is active.
    auto currentChar{ m_board[row][col] };  // char at the current node on the Boggle board

    m_currentWord.push_back(currentChar);   // Add this character to the current word path.

    /* Q_CONDITION: 'q' on the board is interpreted as 'qu' as a convenience since 
    they often go together. When this occurs, the qActive flag is set, and both
    'q' and 'u' are added to the current word. Anytime a char is removed when the
    qCondition is active, an extra char needs to be removed to account for the extra
    'u' that was pushed onto the word. */
    if (currentChar == 'q')
    {
        m_currentWord.push_back('u');
        qCondition = true;
    }


    // If the current word (which includes the chars in this iteration) is a valid dictionary path
    if (m_dictionary->findPrefix(m_currentWord))
    {
        // We are visting this node, add it to the set.
        m_visitedNodes.insert({ row, col });

        // Check all possible 8 directions around the current node for another valid node.
        BoardNodes validNodes{};
        checkNodeUp         (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeUpRight    (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeRight      (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeDownRight  (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeDown       (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeDownLeft   (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeUpLeft     (row, col, m_board, validNodes, m_visitedNodes);
        checkNodeLeft       (row, col, validNodes, m_visitedNodes);

        // Go through all the valid nodes (if any) and recurse.
        for (const auto& node : validNodes)
        {
            findWords(node.first, node.second); // !! RECURSIVE CALL !!
        }

        /* When we are done looking beyond the current node to any active nodes,
        check to see if this current word is a valid word in the dictionary. If
        it is, add it to the set of answers. */
        if (m_dictionary->searchWord(m_currentWord))
        {
            m_answers.insert(m_currentWord);
        }

        /* Erase this recuse call's character node from the visited nodes set since we are 
        done with this specific word path. */
        m_visitedNodes.erase({ row, col }); 
    }

    /* About to exit recurse call, remove this nodes char from the current word since we are
    done with this specific word path. */
    m_currentWord.pop_back();

    /* When the Q_CONDITION (see above) is active, an extra char needs 
    to be removed from the current word.*/
    if (qCondition)
    {
        m_currentWord.pop_back(); // Removes the 'q' because the extra 'u' was already removed.
    }
}
