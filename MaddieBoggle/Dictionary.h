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
/// 
/// </summary>
struct LetterNode
{
#ifdef _DEBUG
    LetterNode() { nodeCount++; }
#endif

    ~LetterNode()
    {
#ifdef _DEBUG
        killCount++;
#endif
        for (const auto& pair : m_childLetters)
        {
            delete pair.second;
        }
    }

    unordered_map<char, LetterNode*> m_childLetters;
    bool m_isWordValid = false;
};


/// <summary>
/// 
/// </summary>
class Dictionary
{
public:
    Dictionary();
    ~Dictionary();

    void insertWord(const string& word);
    bool searchWord(const string& word) const;
    bool findPrefix(const string& prefix) const;
    int importDictionary(const string& filepath);

private:
    static constexpr size_t m_minWordSize{ 3 };
    size_t m_wordCount;         // number of words imported
    LetterNode* m_root;         // root node for the trie
};


#endif // DICTIONARY_H
