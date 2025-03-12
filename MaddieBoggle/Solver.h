#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "WordTrie.h"


using namespace std;

#pragma once
//
//#include <memory>
//#include <unordered_set>
//#include <vector>
//
//#include "utility.h"
//#include "WordTrie.h"
//
//
//static inline void checkNodeUp(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) - c_boardLineLength };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeUpLeft(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) - c_boardLineLength - 1 };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeUpRight(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) - c_boardLineLength + 1 };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeRight(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) + 1 };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeDownRight(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) + c_boardLineLength + 1 };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeDown(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) + c_boardLineLength };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeDownLeft(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) + c_boardLineLength - 1 };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//static inline void checkNodeLeft(size_t& currentIndex, unordered_set<size_t>& validNodes, unordered_set<size_t>& visitedNodes)
//{
//	auto nextIndex{ static_cast<int>(currentIndex) - 1 };
//	if ((nextIndex >= 0) && (visitedNodes.find(nextIndex) == visitedNodes.end()) && (nextIndex < (c_boardLineLength * c_boardLineHeight)))
//	{
//		validNodes.insert(nextIndex);
//	}
//}
//
//
//class Solver
//{
//public:
//	Solver(const vector<char>& board, shared_ptr<const WordTrie> dictionary) :
//		m_board(board),
//		m_dictionary(dictionary),
//		m_visitedNodes(),
//		m_answers(),
//		m_currentWord("")
//	{
//		assert(dictionary);
//	}
//
//
//	void findWords(size_t index)
//	{
//		m_currentWord.push_back(m_board[index]); // update current word to include this node into the path
//
//		// if the current word + this node is a valid dictionary path
//		if (m_dictionary->findPrefix(m_currentWord))
//		{
//			m_visitedNodes.insert(index);
//
//			unordered_set<size_t> validNodes{};
//			checkNodeUp(index, validNodes, m_visitedNodes);
//			checkNodeUpRight(index, validNodes, m_visitedNodes);
//			checkNodeRight(index, validNodes, m_visitedNodes);
//			checkNodeDownRight(index, validNodes, m_visitedNodes);
//			checkNodeDown(index, validNodes, m_visitedNodes);
//			checkNodeDownLeft(index, validNodes, m_visitedNodes);
//			checkNodeLeft(index, validNodes, m_visitedNodes);
//			checkNodeUpLeft(index, validNodes, m_visitedNodes);
//			
//			for (const auto& node : validNodes)
//			{
//				findWords(node);
//			}
//
//			if (m_dictionary->searchWord(m_currentWord))
//			{
//				m_answers.insert(m_currentWord);
//			}
//
//			m_visitedNodes.erase(index); // done erase node and allow return to recursive callee
//			m_currentWord.pop_back(); // we are returning, so remove the current char from this node
//		}
//		else
//		{
//			//m_visitedNodes.erase(index); // done erase node and allow return to recursive callee
//			m_currentWord.pop_back(); // we are returning, so remove the current char from this node
//		}
//	}
//
//
//private:
//	const vector<char>& m_board;
//	shared_ptr<const WordTrie> m_dictionary;
//
//	unordered_set<size_t> m_visitedNodes;
//	unordered_set<string> m_answers;
//	string m_currentWord;
//
//
//
//
//
//	
//};

struct PairHash 
{
    std::size_t operator()(const std::pair<size_t, size_t>& p) const 
    {
        return std::hash<size_t>()(p.first) ^ (std::hash<size_t>()(p.second) << 1);
    }
};


class Solver
{
    using BoardNodes = unordered_set<pair<size_t, size_t>, PairHash>;

public:
    Solver(shared_ptr<const WordTrie> dictionary, const vector<vector<char>>& board) :
        m_dictionary(dictionary),
        m_board(board),
		m_visitedNodes(),
		m_answers(),
		m_currentWord("")
    {
        assert(m_dictionary);
    }


    void findWords(size_t row, size_t col)
	{
		m_currentWord.push_back(m_board[row][col]); // update current word to include this node into the path

		// if the current word + this node is a valid dictionary path
		if (m_dictionary->findPrefix(m_currentWord))
		{
            m_visitedNodes.insert({ row, col });

            BoardNodes validNodes{};
			checkNodeUp(row, col, validNodes);
			//checkNodeUpRight(index, validNodes, m_visitedNodes);
			//checkNodeRight(index, validNodes, m_visitedNodes);
			//checkNodeDownRight(index, validNodes, m_visitedNodes);
			//checkNodeDown(index, validNodes, m_visitedNodes);
			//checkNodeDownLeft(index, validNodes, m_visitedNodes);
			//checkNodeLeft(index, validNodes, m_visitedNodes);
			//checkNodeUpLeft(index, validNodes, m_visitedNodes);
			
			for (const auto& node : validNodes)
			{
				findWords(row, col);
			}

			if (m_dictionary->searchWord(m_currentWord))
			{
				m_answers.insert(m_currentWord);
			}

            m_visitedNodes.erase({ row, col }); // done erase node and allow return to recursive callee
			m_currentWord.pop_back(); // we are returning, so remove the current char from this node
		}
		else
		{
			m_currentWord.pop_back(); // we are returning, so remove the current char from this node
		}
	}




private:
    shared_ptr<const WordTrie> m_dictionary;
    const vector<vector<char>>& m_board;
    BoardNodes m_visitedNodes;
	unordered_set<string> m_answers;
	string m_currentWord;

    inline void checkNodeUp(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newRow{ (int)row - 1 };

        if (newRow >= 0) // (literal edge case) if not on the top edge of the board
        {
            if (m_board[newRow].size() > col) // (edgier case) if the above index even exists
            {
                auto temp{ make_pair(size_t(newRow), col) };
                if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
                {
                    validNodes.insert(temp);
                }
            }
        }
    }
};




