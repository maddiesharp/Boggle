//
// Place Holder Copyright Header
//

#include <fstream>

#ifdef _DEBUG
#include <cassert>
#include <iostream>
#endif

#include "BoggleSolver.h"
#include "BoggleSolverHelper.h"


/// <summary>
/// Class constructor for the boggle solver.
/// </summary>
/// <param name="dictionary">shared_ptr to a const dictionary of valid words</param>
/// <param name="pool">shared ptr to a thread pool</param>
/// <param name="board">const reference to a board to traverse when looking for words</param>
BoggleSolver::BoggleSolver(shared_ptr<const Dictionary> dictionary, shared_ptr<ThreadPool> pool, const BoggleBoard& board) :
    m_board(board),
    m_dictionary(dictionary),
    m_pool(pool),
    m_answersMutex(),
    m_answers()
{
    assert(m_dictionary);
    assert(m_pool);
}


/// <summary>
/// Adds a task to the thread pool for every node on the boggle board.
/// </summary>
void BoggleSolver::solveBoard()
{
    size_t rowIndex{ 0 };
    size_t colIndex{ 0 };
    for (const auto& row : m_board)
    {
        colIndex = 0;
        for (const auto& col : row)
        {
            m_pool->queueTask([this, rowIndex, colIndex]() {
                this->findWordsAtIndex(rowIndex, colIndex);
            });
            colIndex++;
        }
        rowIndex++;
    }
}


/// <summary>
/// Outputs all the boggle board answers to a file at the provided location.
/// </summary>
/// <param name="filepath">output file destination for all the answers</param>
void BoggleSolver::exportAnswers(const string& filepath)
{
    ofstream output;
    output.open(filepath);

    if (output.is_open())
    {
        lock_guard<mutex> lock(m_answersMutex); // just in case
        for (const auto& ans : m_answers)
        {
            output << ans << endl;
        }
        output.close();
    }
    else
    {
        cerr << "Error: Could not open file for writing at path: " << filepath << "\n";
    }
}


/// <summary>
/// This method is the main execution point that threads will call in order to solve
/// a portion of the boggle board. The first call to this method takes a specific
/// character index in the boggle board. This kicks off a recursive depth-first-search alg
/// that keeps traversing all possible nodes. The following search rules are implemented:
/// - node traversal is acyclic (not loop-backs, ie no touching visited nodes)
/// - if an adjacent node doesn't form a word prefix, there is no need to travel to
///     to it since it could not possible form a word
/// 
/// This method only finds all the possible words given a single starting node on 
/// the board. It will need to be run once for the total number of character nodes
/// in the boggle board, since there are that many starting nodes to begin looking
/// for words.
/// 
/// Threads running this method will maintain their own volatile data (current word, valid
/// nodes, visited nodes). As such, those fields are marked as "thread_local". The only
/// shared data is the answer set, which is mutex protected.
/// </summary>
/// <param name="row">row index of a character node on the boggle board</param>
/// <param name="col"column index of a character node on the boggle board></param>
void BoggleSolver::findWordsAtIndex(size_t row, size_t col)
{
    /* Each thread running this method will have its own instance
    of these thread_locals. This allows these variables to be considered
    static for recursive calls, without hitting any memory collisions. */
    thread_local string m_currentWord;      
    thread_local BoardNodes m_visitedNodes; 

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
    if (m_dictionary->searchDictionary(m_currentWord, SearchType::PATH))
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
            findWordsAtIndex(node.first, node.second); // !! RECURSIVE CALL !!
        }

        /* When we are done looking beyond the current node to any active nodes,
        check to see if this current word is a valid word in the dictionary. If
        it is, add it to the set of answers. */
        if (m_dictionary->searchDictionary(m_currentWord, SearchType::WORD))
        {
            lock_guard lock(m_answersMutex);
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
