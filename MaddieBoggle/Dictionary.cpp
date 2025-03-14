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
/// Class constructor. Creates the starting root node.
/// </summary>
Dictionary::Dictionary() :
	m_wordCount(0)
{
    m_root = new LetterNode(); // create root of the trie
}


/// <summary>
/// Class destructor. Begins the destruction of all child nodes.
/// </summary>
Dictionary::~Dictionary()
{
	delete m_root; // begins the destruction of all child nodes
#ifdef _DEBUG
    cout << "\tnode count: " << nodeCount << "\n\tkill count: " << killCount << endl;
#endif
}


/// <summary>
/// Inserted a word into the trie, letter by letter. The last letter
/// of the word will have its node marked as 'true'. Returns early if
/// word is too small to be valid or is already in the dictionary, otherwise
/// a word will be considered valid and inserted into the dictionary.
/// </summary>
/// <param name="word">String word to add to the dictionary trie data structure.</param>
void Dictionary::insertWord(const string& word)
{
    assert(m_root);
    assert(word.size() > 0);

    /* Return early if word is a duplicate OR word is too small. */
    if (searchDictionary(word, SearchType::WORD) || (word.size() < m_minWordSize)) return;

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
/// Searches the trie for the provided word. If the word exists in the trie,
/// return true; otherwise, return false. 
/// </summary>
/// <param name="word">Word to search for in the dictionary.</param>
/// <returns>bool true if word exists, otherwise false</returns>
bool Dictionary::searchDictionary(const string& word, SearchType searchType) const
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

    /* Return based on the search type. If we are still traversing the trie
    path, we may want to know if a node exists even if it is not a word. A
    query will only want to search for a valid word at the end of its path. */
    switch (searchType)
    {
        case SearchType::WORD: return currentNode->m_isWordValid;
        case SearchType::PATH: return true;
        default: return false;
    }
}


/// <summary>
/// Imports the dictionary from the provided filepath into the word trie.
/// 
/// The following error codes can be returned:
/// 0 --> success, no error
/// 1 --> unable to open file
/// 2 --> unprecendented error saved by a try-catch block, error is not identified, 
///     so the callee should exit gracefully
/// </summary>
/// <param name="filepath">location of the dictionary file to import</param>
/// <returns>error code</returns>
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
