//
// Place Holder Copyright Header
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cassert>
#include <string>
#include <unordered_map>


using namespace std;


#ifdef _DEBUG
static size_t nodeCount = 0;
static size_t killCount = 0;
#endif


/// <summary>
/// Struct container that represents a letter in a word
/// trie. Any succeeding letters are found in a LetterNode's
/// map where the keys are the characters and the values are
/// the pointer to the next character's LetterNode.
/// 
/// A represents if a character node represents the end of a valid word.
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

    unordered_map<char, LetterNode*> m_childLetters; // map of succeeding chars
    bool m_isWordValid = false; //indicates if node is the end of a valid word
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
