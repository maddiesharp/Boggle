//
// Place Holder Copyright Header
//

#ifndef LETTER_NODE_H
#define LETTER_NODE_H

#include <vector>


using namespace std;


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
    LetterNode();

    vector<pair<char, LetterNode*>> m_childLetters; // sorted vector of succeeding chars
    bool m_isWordValid; //indicates if node is the end of a valid word

    LetterNode* findChild(char letter);
    void insertChild(char letter, LetterNode* child);
};


#endif // LETTER_NODE_H
