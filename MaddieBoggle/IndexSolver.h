//
// Place Holder Copyright Header
//

#ifndef INDEX_SOLVER_H
#define INDEX_SOLVER_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "Dictionary.h"


using namespace std;


/**/
class IndexSolver
{
public:
    IndexSolver(shared_ptr<const Dictionary> dictionary, const vector<vector<char>>& board);

    void findWords(size_t row, size_t col);

    /**/
    struct PairHash {
        std::size_t operator()(const pair<size_t, size_t>& p) const {
            return std::hash<size_t>()(p.first) ^ (std::hash<size_t>()(p.second) << 1);
        }};

    using BoardNodes = unordered_set<pair<size_t, size_t>, PairHash>;

private:
    const vector<vector<char>>& m_board;
    shared_ptr<const Dictionary> m_dictionary;
    
    string m_currentWord;
    unordered_set<string> m_answers;
    BoardNodes m_visitedNodes;
};


#endif // INDEX_SOLVER_H
