#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;


#ifdef _DEBUG
size_t nodeCount = 0;
size_t killCount = 0;
#endif


/**/
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


/**/
class WordTrie
{
public:
    WordTrie() : m_wordCount(0)
    {
        m_root = new LetterNode();
    }


    ~WordTrie()
    {
        delete m_root; // begins the destruction of all nodes
    }


    void insertWord(const string& word)
    {
        assert(m_root);
        assert(word.size() > 0);

        // skip duplicate words OR words that are too small
        if (searchWord(word) || (word.size() < m_minWordSize)) return;

        auto currentNode{ m_root }; // start at the root
        for (const auto& letter : word)
        {
            // if letter is not present in the node map
            if (currentNode->m_childLetters.find(letter) == currentNode->m_childLetters.end())
            {
                currentNode->m_childLetters[letter] = new LetterNode();
            }

            // move into the matching node to check for the next letter
            currentNode = currentNode->m_childLetters[letter];
        }

        // set the current node to true at the end of this word
        currentNode->m_isWordValid = true;
        m_wordCount++;
    }


    bool searchWord(const string& word) const
    {
        assert(m_root);
        assert(word.size() > 0);

        auto currentNode{ m_root };
        for (const auto& letter : word)
        {
            // if letter could not be found, then we know that combo of letters doesn't lead to a real word
            if (currentNode->m_childLetters.find(letter) == currentNode->m_childLetters.end())
            {
                return false;
            }

            // move into next node to check for any matching letters
            currentNode = currentNode->m_childLetters[letter];
        }

        // we made it to the last letter, return valid word to confirm/deny path is valid
        return currentNode->m_isWordValid;
    }


    bool findPrefix(const string& prefix) const
    {
        assert(m_root);
        assert(prefix.size() > 0);

        auto currentNode{ m_root };
        for (const auto& letter : prefix)
        {
            // if letter could not be found, then we know that some part of the prefix doesn't exist
            if (currentNode->m_childLetters.find(letter) == currentNode->m_childLetters.end())
            {
                return false;
            }

            // move into next node to check for any matching letters
            currentNode = currentNode->m_childLetters[letter];
        }

        return true;
    }


    int importDictionary(const string& filepath)
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
            while (file >> word) // import words line-by-line
            {
                insertWord(word);
            }

            file.close();

            cout << "Imported word count: " << m_wordCount << "\n";
            return 0;
        }
        catch (...)
        {
            cerr << "Unexpected error when importing dictionary file!\n";
            return 2;
        }
    }


private:
    LetterNode* m_root;         // root node for the trie
    size_t m_wordCount;         // number of words imported
    static constexpr size_t m_minWordSize{ 3 };
};
