//
// Place Holder Copyright Header
//

#include <fstream>
#include <iostream>

#ifdef _DEBUG
#include <cassert>
#endif

#include "Dictionary.h"


/// <summary>
/// 
/// </summary>
Dictionary::Dictionary() :
	m_wordCount(0)
{
	m_root = new LetterNode(); // create root of the trie
}


/// <summary>
/// 
/// </summary>
Dictionary::~Dictionary()
{
	delete m_root; // begins the destruction of all child nodes
#ifdef _DEBUG
    cout << "\tnode count: " << nodeCount << "\n\tkill count: " << killCount << endl;
#endif
}


/// <summary>
/// 
/// </summary>
/// <param name="word"></param>
void Dictionary::insertWord(const string& word)
{
    assert(m_root);
    assert(word.size() > 0);

    /* Return early if word is a duplicate OR word is too small. */
    if (searchWord(word) || (word.size() < m_minWordSize)) return;

    auto currentNode{ m_root };
    for (const auto& letter : word)
    {
        /* If letter could not be found, then a node for it needs to be created. */
        if (currentNode->m_childLetters.find(letter) == currentNode->m_childLetters.end())
        {
            currentNode->m_childLetters[letter] = new LetterNode();
        }

        // Move into the matching node to check for the next letter.
        currentNode = currentNode->m_childLetters[letter];
    }

    // End of word insertion, set current node's word valid flag as true.
    currentNode->m_isWordValid = true;

#ifdef _DEBUG
    m_wordCount++;
#endif
}


/// <summary>
/// 
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
bool Dictionary::searchWord(const string& word) const
{
    assert(m_root);
    assert(word.size() > 0);

    auto currentNode{ m_root };
    for (const auto& letter : word)
    {
        /* If letter could not be found, then we know this combo of 
        letters doesn't lead to a real word. We can return early. */
        if (currentNode->m_childLetters.find(letter) == currentNode->m_childLetters.end())
        {
            return false; // early return
        }

        /* If the early return did not happen, then the node for the
        next letter exists. */
        currentNode = currentNode->m_childLetters[letter];
    }

    // At the final letter, check if word is valid and return.
    return currentNode->m_isWordValid;
}


/// <summary>
/// 
/// </summary>
/// <param name="prefix"></param>
/// <returns></returns>
bool Dictionary::findPrefix(const string& prefix) const
{
    assert(m_root);
    assert(prefix.size() > 0);

    auto currentNode{ m_root };
    for (const auto& letter : prefix)
    {
        /* If letter could not be found, then we know this combo of
        letters doesn't lead to a real word. We can return early. */
        if (currentNode->m_childLetters.find(letter) == currentNode->m_childLetters.end())
        {
            return false; // early return
        }

        /* If the early return did not happen, then the node for the
        next letter exists. */
        currentNode = currentNode->m_childLetters[letter];
    }

    return true;
}


/// <summary>
/// 
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
int Dictionary::importDictionary(const string& filepath)
{
    try
    {
        ifstream file(filepath);
        if (!file)
        {
            cerr << "Error finding file at path: " << filepath << ".\n";
            return 1;
        }

        string word{};
        while (file >> word) // Import words line-by-line
        {
            insertWord(word);
        }

        file.close();
#ifdef _DEBUG
        cout << "Imported word count: " << m_wordCount << "\n";
#endif
        return 0;
    }
    catch (...)
    {
        cerr << "Unexpected error when importing dictionary file!\n";
        return 2;
    }
}
