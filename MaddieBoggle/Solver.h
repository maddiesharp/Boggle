#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "WordTrie.h"


using namespace std;


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
        bool qActive{ false };
        auto currentChar{ m_board[row][col] };

        if (currentChar == 'q')
        {
            m_currentWord.push_back(currentChar);
            m_currentWord.push_back('u');
            qActive = true;
        }
        else
        {
            m_currentWord.push_back(currentChar); // update current word to include this node into the path
        }

		// if the current word + this node is a valid dictionary path
		if (m_dictionary->findPrefix(m_currentWord))
		{
            m_visitedNodes.insert({ row, col });

            BoardNodes validNodes{};
			checkNodeUp         (row, col, validNodes);
			checkNodeUpRight    (row, col, validNodes);
			checkNodeRight      (row, col, validNodes);
			checkNodeDownRight  (row, col, validNodes);
			checkNodeDown       (row, col, validNodes);
			checkNodeDownLeft   (row, col, validNodes);
			checkNodeLeft       (row, col, validNodes);
			checkNodeUpLeft     (row, col, validNodes);
			
			for (const auto& node : validNodes)
			{
				findWords(node.first, node.second);
			}

			if (m_dictionary->searchWord(m_currentWord))
			{
				m_answers.insert(m_currentWord);
			}

            m_visitedNodes.erase({ row, col }); // done erase node and allow return to recursive callee
			m_currentWord.pop_back(); // we are returning, so remove the current char from this node

            if (qActive)
            {
                m_currentWord.pop_back();
            }
		}
		else
		{
			m_currentWord.pop_back(); // we are returning, so remove the current char from this node

            if (qActive)
            {
                m_currentWord.pop_back();
            }
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

    inline void checkNodeUpRight(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newRow{ (int)row - 1 };
        const int newCol{ (int)col + 1 };

        if (newRow >= 0) // (literal edge case) if not on the top edge of the board
        {
            if (m_board[newRow].size() > newCol) // (edgier case) if the above index even exists
            {
                auto temp{ make_pair(size_t(newRow), newCol) };
                if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
                {
                    validNodes.insert(temp);
                }
            }
        }
    }

    inline void checkNodeRight(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newCol{ (int)col + 1 };

        if (newCol < m_board[row].size()) // (literal edge case) if not on the right edge of the board
        {
            auto temp{ make_pair(size_t(row), newCol) };
            if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
            {
                validNodes.insert(temp);
            }
        }
    }

    inline void checkNodeUpLeft(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newRow{ (int)row - 1 };
        const int newCol{ (int)col - 1 };

        if ((newRow >= 0) && (newCol >= 0)) // (literal edge case) if not on the top/left edges of the board
        {
            if (m_board[newRow].size() > newCol) // (edgier case) if the above index even exists
            {
                auto temp{ make_pair(size_t(newRow), newCol) };
                if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
                {
                    validNodes.insert(temp);
                }
            }
        }
    }

    inline void checkNodeDown(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newRow{ (int)row + 1 };

        if (newRow < m_board.size()) // (literal edge case) if not on the bottom edge of the board
        {
            if (m_board[newRow].size() > col) // (edgier case) if the below index even exists
            {
                auto temp{ make_pair(size_t(newRow), col) };
                if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
                {
                    validNodes.insert(temp);
                }
            }
        }
    }

    inline void checkNodeDownRight(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newRow{ (int)row + 1 };
        const int newCol{ (int)col + 1 };

        if (newRow < m_board.size()) // (literal edge case) if not on the bottom edge of the board
        {
            if (m_board[newRow].size() > newCol) // (edgier case) if the below index even exists
            {
                auto temp{ make_pair(size_t(newRow), newCol) };
                if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
                {
                    validNodes.insert(temp);
                }
            }
        }
    }

    inline void checkNodeDownLeft(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newRow{ (int)row + 1 };
        const int newCol{ (int)col - 1 };

        if (newRow < m_board.size() && (newCol >= 0)) // (literal edge case) if not on the bottom/left edges of the board
        {
            if (m_board[newRow].size() > newCol) // (edgier case) if the below index even exists
            {
                auto temp{ make_pair(size_t(newRow), newCol) };
                if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
                {
                    validNodes.insert(temp);
                }
            }
        }
    }

    inline void checkNodeLeft(size_t& row, size_t& col, BoardNodes& validNodes)
    {
        const int newCol{ (int)col - 1 };

        if (newCol >= 0) // (literal edge case) if not on the left edge of the board
        {
            auto temp{ make_pair(size_t(row), newCol) };
            if (m_visitedNodes.find(temp) == m_visitedNodes.end()) // index hasn't already been visited
            {
                validNodes.insert(temp);
            }
        }
    }


};




