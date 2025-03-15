//
// Place Holder Copyright Header
//

#ifndef LETTER_NODES_H
#define LETTER_NODES_H

#include <algorithm>
#include <cassert>
#include <vector>


using namespace std;


struct LetterNode;

class LetterNodePool
{
public:
    /// <summary>
    /// Class constructor. Provided size must be greater than 0.
    /// </summary>
    /// <param name="poolSize">number of node objects to reserve on the heap</param>
    LetterNodePool(size_t poolSize)
    {
        assert(poolSize > 0);
        m_pool.reserve(poolSize); // ensures the pool vector doesn't dynamically resize

        for (size_t i = 0; i < poolSize; ++i)
        {
            /* create a node object on the pool and get its reference, then 
            take the newly created reference and add its address to the available 
            nodes list */
            LetterNode& node { m_pool.emplace_back() };
            m_freeNodes.push_back(&node);
        }
    }

    /// <summary>
    /// Allocates a node by returning the next available address of one.
    /// If there are no more allocatable nodes, return nullptr. Callee is
    /// responsible for handling.
    /// Allocated node is removed from the free pool.
    /// </summary>
    /// <returns>Pointer to available node, otherwise nullptr</returns>
    LetterNode* allocate()
    {
        if (m_freeNodes.empty())
        {
            cerr << "Out of allocation space! Dictionary too large.\n";
            return nullptr;
        }

        auto node{ m_freeNodes.back() };    // get a free node address
        m_freeNodes.pop_back();             // remove acquired node address from the free nodes
        return node;
    }


    /// <summary>
    /// Puts a deleted node back into the allocation pool.
    /// </summary>
    /// <param name="node">Node address to reallocate.</param>
    void deallocate(LetterNode* node)
    {
        m_freeNodes.push_back(node);
    }


private:
    vector<LetterNode> m_pool;          // reserved memory
    vector<LetterNode*> m_freeNodes;    // contains pointers to all the reserved memory blocks that are available for allocation
};


/// <summary>
/// Struct container that represents a letter in a word
/// trie. Any succeeding letters are found in a LetterNode's
/// vector where pairs of characters and pointers to the 
/// corresponding sequential LetterNodes.
/// 
/// Each node has a bool used to indicate if that node is the 
/// end of word. 
/// </summary>
struct LetterNode
{
    LetterNode() = default; // needed for unit tests to compile the emplace_back in pool initialization

    vector<pair<char, LetterNode*>> m_childLetters; // sorted vector of succeeding chars
    bool m_isWordValid = false; //indicates if node is the end of a valid word

    /// <summary>
    /// Searches a node's m_childLetters vector for the provided char. If the 
    /// char was found, return the LetterNode*; otherwise, return nullptr.
    /// </summary>
    /// <param name="letter">Char letter that is being searched for</param>
    /// <returns>pointer to the node where the char exists, nullptr if it doesn't</returns>
    LetterNode* findChild(char letter)
    {
        /* Same lower bound binary search used in the insertChild(...) function below. */
        auto it{ lower_bound(m_childLetters.begin(), m_childLetters.end(), letter,
            [](const auto& pair, char value) { return pair.first < value; }) };

        //               !! ORDER OF CONDITIONAL CHECKS MATTERS !!
        //                (for the same reason as insertChild(...)
        return ((it != m_childLetters.end() && it->first == letter) ? it->second : nullptr);
    }

    /// <summary>
    /// Inserts the provided char and LetterNode* into the vector of children while
    /// keeping it sorted in ascending order of chars. Duplicate chars (and the node) 
    /// will not be added to the vector.
    /// </summary>
    /// <param name="letter">char letter we want to insert</param>
    /// <param name="child">the LetterNode* that accompanies the char in a pair</param>
    void insertChild(char letter, LetterNode* child)
    {
        /* Use lower bound to run a binary search on the sorted vector. Vector remains
        sorted by override the implicit std::less{} with a lambda that is compatible
        with this vector of pairs.

        The iterator will point to the position where the letter can be inserted while
        preserving the sorted order.*/
        auto it{ lower_bound(m_childLetters.begin(), m_childLetters.end(), letter,
            [](const auto& pair, char value) { return pair.first < value; }) };

        /*                !! ORDER OF CONDITIONAL CHECKS MATTERS !!

        it == m_childLetters.end() : if the char we are searching for would be the highest
            value char in the vector and isn't already present, then the iterator will
            point to the end of the vector.

            -OR-

        it->first != letter : if the iterator that was returned doesn't already point to
            a pair that includes the char - this prevents duplicate chars from being added.*/
        if (it == m_childLetters.end() || it->first != letter)
        {
            m_childLetters.insert(it, { letter, child });
        }
    }
};


#endif // LETTER_NODES_H
