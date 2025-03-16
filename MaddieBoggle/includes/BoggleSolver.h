//
// Place Holder Copyright Header
//

#ifndef BOGGLE_SOLVER_H
#define BOGGLE_SOLVER_H

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "BoggleBoard.h"
#include "Dictionary.h"
#include "ThreadPool.h"


using namespace std;


/// <summary>
/// The BoggleSolver class is built to solve all the words that can be made
/// from a given boggle board. Words are found on a per-starter-node basis, 
/// which means when the search algorithm is called, it only looks for words
/// that start at the given row and column.
/// 
/// This type of architecture allows multiple threads to search for words at
/// different indexes at the same time. In order to keep the board and dictionary
/// thread-safe, they are shared to this class in some constant form. 
/// 
/// Each of the search threads will keep track of their own data. The only risk of
/// collisions is with the ORDERED set where all the threads will store found
/// words. The set is protected with a mutex to prevent collisions.
///  
/// After searching all the nodes on the board, this class can be instructed to 
/// log all the found words to a file at the provided filepath.
/// </summary>
class BoggleSolver
{
public:
    BoggleSolver(shared_ptr<const Dictionary> dictionary, shared_ptr<ThreadPool> pool, const BoggleBoard& board);

    void solveBoard();
    void exportAnswers(const string& filepath);

    /* C++17 doesn't have a hash function for type std::pair, so one 
    needs to be provided for the unordered_set to hash correctly. */
    struct PairHash {
        std::size_t operator()(const pair<size_t, size_t>& p) const {
            return std::hash<size_t>()(p.first) ^ (std::hash<size_t>()(p.second) << 1);
        }};

    using BoardNodes = unordered_set<pair<size_t, size_t>, PairHash>;

protected:
    set<string> m_answers;      // using set here because it automatically sorts string alphabetically
    void findWordsAtIndex(size_t row, size_t col);

private:
    const BoggleBoard& m_board;                 // thread safe board, using BoggleBoard = vector<vector<char>>
    shared_ptr<const Dictionary> m_dictionary;  // thread safe dictionary 
    shared_ptr<ThreadPool> m_pool;              // access to execution threads
    
    mutex m_answersMutex;       // mutex used to protect access to the combined set of found answers
    
};


#endif // BOGGLE_SOLVER_H
