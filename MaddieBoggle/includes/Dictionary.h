//
// Place Holder Copyright Header
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

#include "LetterNodes.h"


using namespace std;


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
    Dictionary(size_t poolSize);

    int importDictionary(const string& filepath);
    int insertWord(const string& word);
    bool searchDictionary(const string& word, SearchType searchType) const;

private:
    static constexpr size_t m_minWordSize{ 3 };
    size_t m_wordCount;         // number of words imported
    LetterNode* m_root;         // root node for the trie
    LetterNodePool m_pool;
};


#endif // DICTIONARY_H
