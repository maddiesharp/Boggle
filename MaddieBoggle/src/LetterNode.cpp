//
// Place Holder Copyright Header
//

#include <algorithm>

#include "LetterNode.h"


/// <summary>
/// Class constructor
/// </summary>
LetterNode::LetterNode() :
	m_childLetters(),
	m_isWordValid(false)
{
	// intentionally blank
}


/// <summary>
/// Searches a node's m_childLetters vector for the provided char. If the 
/// char was found, return the LetterNode*; otherwise, return nullptr.
/// </summary>
/// <param name="letter">Char letter that is being searched for</param>
/// <returns>pointer to the node where the char exists, nullptr if it doesn't</returns>
LetterNode* LetterNode::findChild(char letter)
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
void LetterNode::insertChild(char letter, LetterNode* child)
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

