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
/// The IndexSolver class is built to solve all the words that can be made
/// from a given started character node on the boggle board
/// 
/// TODO more info
/// 
/// </summary>
class BoggleSolver
{
public:
    BoggleSolver(shared_ptr<const Dictionary> dictionary, shared_ptr<ThreadPool> pool, const BoggleBoard& board);

    void solveBoard();
    void findWordsAtIndex(size_t row, size_t col);
    void exportAnswers(const string& filepath);

    /* C++17 doesn't have a hash function for type std::pair, so one needs to be provided. */
    struct PairHash {
        std::size_t operator()(const pair<size_t, size_t>& p) const {
            return std::hash<size_t>()(p.first) ^ (std::hash<size_t>()(p.second) << 1);
        }};

    using BoardNodes = unordered_set<pair<size_t, size_t>, PairHash>;

private:
    const BoggleBoard& m_board;                 // thread safe board, using BoggleBoard = vector<vector<char>>
    shared_ptr<const Dictionary> m_dictionary;  // thread safe dictionary 
    shared_ptr<ThreadPool> m_pool;              // access to execution threads
    
    mutex m_answersMutex;       // mutex used to protect access to the combined set of found answers
    set<string> m_answers;      // using set here because it automatically sorts string alphabetically
};


#endif // BOGGLE_SOLVER_H
