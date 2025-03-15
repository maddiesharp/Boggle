//
// Place Holder Copyright Header
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <algorithm>
#include <string>
#include <vector>


using namespace std;


#ifdef _DEBUG
static size_t nodeCount = 0;
static size_t killCount = 0;
#endif


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
#ifdef _DEBUG
    LetterNode() { nodeCount++; }
#endif

    /// <summary>
    /// LetterNode destructor that deletes all child nodes in its map.
    /// </summary>
    ~LetterNode()
    {
#ifdef _DEBUG
        killCount++;
#endif
        for (const auto& pair : m_childLetters)
        {
            delete pair.second; // Causes the child node to begin destructing.
        }
    }

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


/// <summary>
/// There are different search types that use almost the exact same search method.
/// This enum class allows the callee to differentiate the return value it wants.
/// </summary>
enum class SearchType
{
    WORD,
    PATH
};


/// <summary>
/// The Dictionary class is a lean version of a character trie where a 
/// node only contains pointers to nodes that can be appended to create 
/// a valid word. See the example below.
/// 
/// dictionary: ant, and, bat, but
/// 
///             root
///            /    \
///           a      b
///          /      / \
///         n      u   a
///        / \     |   |
///       d   t    t   t
/// 
/// The 'b' node will never point to an 'o' node unless there is a word like
/// "bot" present in the dictionary. In this example, there is not.
/// 
/// The dictionary trie is acyclic.
/// 
/// </summary>
class Dictionary
{
public:
    Dictionary();
    ~Dictionary();

    void insertWord(const string& word);
    bool searchDictionary(const string& word, SearchType searchType) const;
    int importDictionary(const string& filepath);

private:
    static constexpr size_t m_minWordSize{ 3 };
    size_t m_wordCount;         // number of words imported
    LetterNode* m_root;         // root node for the trie
};


#endif // DICTIONARY_H
