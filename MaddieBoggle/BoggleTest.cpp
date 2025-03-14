// BoggleTest.cpp
//
// Programming Rules:
//  1. Any C++ compiler may be used.  Preferably VS2010, VS2012, or VS2015.
//     A. Please document which compiler (including version) was used.
//     B. Include make files or project files where appropriate.
//     C. Document target platform (Windows 32bit, Windows 64bit, Unix, etc.)
//     D. If you don't have a compiler, we recommend downloading Visual Studio
//        Community for Windows, or XCode for Mac (both are free)
//  2. Any core language feature in the latest C++ standard may be used
//  3. All of the standard library may be used, including latest standards or
//     or technical reports.
//  4. 3rd Party libraries (such as Boost) are not allowed
//  5. Submit all source files needed to build final executable
//
// Game Rules:
//  Boggle is a word game.  The goal is to make as many words as possible
//  out of the given set of letters laid out in a 4x4 grid.  Words are
//  formed by starting with any letter and moving to an adjacent letter
//  (up, down, left, right, or diagonal) and so-forth on.  Once a letter
//  is used in a word, it can not be used again.  All words must be a
//  minimum of 3 characters in length.  Finally, in this version, a "q"
//  present on the board will always represent "qu", since "u" nearly always
//  follows "q" in English.  If a word may be formed multiple ways on the same
//  board, it only counts once.
//
// Example:
//
// Board:
//    P W Y R
//    E N T H
//    G S I Q
//    O L S A
//
// A few possible words:
//   pen
//   peg
//   quit
//   hit
//   slit
//   slits
//
// Command line arguments:
//  BoggleTest.exe <dictionary_filename> <board_filename> <output_filename>
//
// Dictionary:
//  The dictionary file is an ASCII text file that lists acceptable words.  Each word is
//  new line separated.  Words are in alphabetical order and all lowercase, utilizing
//  only letters 'a' to 'z'.
//
// Board:
//  The board file is an ASCII text file that is 4 lines of 4 characters.  These
//  represent the game board, a 4x4 matrix of characters.  These may be mixed case.
//  Whitespace is optional and should be ignored.  Only letters 'a' to 'z' or 'A'
//  to 'Z' are used.
//
// Output:
//  The output should be an ASCII text file (in alphabetical order) of all legal words
//  possible to spell on the current board that are in the given dictionary.  These
//  should be all lowercase and newline separated (same format as the dictionary).
//
// Notes:
//  Your final solution should be PRODUCTION QUALITY, as if it is getting checked
//  in to live production code.
//
//  This test file is confidential. No part of this document may be disclosed publicly 
//  without prior written consent from ZeniMax Media, Inc.

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>

#include "BoggleBoard.h"
#include "Dictionary.h"
#include "IndexSolver.h"
#include "ThreadPool.h"

#define METRICS


using namespace std;


int main(const int argc, const char* const argv[])
{
    // PROCESS CLI ARGS --------------------------------------------------------
    if (argc != 4)
    {
        std::cerr << "Usage: BoggleTest <dictionary_filename> <board_filename> <output_filename>" << std::endl;
        return -1;
    }

    const string dictionaryPath { argv[1] };
    const string boardPath      { argv[2] };
    const string outputPath     { argv[3] };

    // CREATE THREAD POOL ------------------------------------------------------
#if defined(_DEBUG) || defined(METRICS)
    auto startTime{ chrono::high_resolution_clock::now() };
#endif

    auto threadPool{ ThreadPool() };


    // IMPORT DICTIONARY -------------------------------------------------------
#if defined(_DEBUG) || defined(METRICS)
    auto importDictionaryTime{ chrono::high_resolution_clock::now() };
#endif

    auto tempDictionary{ make_unique<Dictionary>() };
    auto errCode{ tempDictionary->importDictionary(dictionaryPath) };
    if (errCode > 0)
    {
        return errCode;
    }
    shared_ptr<const Dictionary> threadSafeDictionary{ move(tempDictionary) };


#if defined(_DEBUG) || defined(METRICS)
    auto importTrieEndTime{ chrono::high_resolution_clock::now() };
#endif

    // IMPORT BOARD ------------------------------------------------------------
    BoggleBoard board{};
    errCode = importBoard(boardPath, board);
    if (errCode > 0)
    {
        return errCode;
    }

#if defined(_DEBUG) || defined(METRICS)
    auto solverStartTime{ chrono::high_resolution_clock::now() };
#endif

    // SOLVE BOARD -------------------------------------------------------------
    auto x = [&threadSafeDictionary, &board](size_t row, size_t col)
    {
        IndexSolver solver{ threadSafeDictionary, board };
#ifdef _DEBUG
        cout << "Boggling at row,col: " << row << "," << col << "\n";
#endif
        solver.findWords(row, col);
    };

    size_t rowIndex{ 0 };
    size_t colIndex{ 0 };
    for (const auto& row : board)
    {
        colIndex = 0;
        for (const auto& col : row)
        {
            x(rowIndex, colIndex);
            colIndex++;
        }
        rowIndex++;
    }

    //IndexSolver solver{ threadSafeDictionary, board };
    //solver.findWords(0, 0);
    //solver.findWords(0, 1);
    //solver.findWords(0, 2);
    //solver.findWords(0, 3);
    //solver.findWords(1, 0);
    //solver.findWords(1, 1);
    //solver.findWords(1, 2);
    //solver.findWords(1, 3);
    //solver.findWords(2, 0);
    //solver.findWords(2, 1);
    //solver.findWords(2, 2);
    //solver.findWords(2, 3);
    //solver.findWords(3, 0);
    //solver.findWords(3, 1);
    //solver.findWords(3, 2);
    //solver.findWords(3, 3);

    // EXPORT SORTED ANSWERS ---------------------------------------------------



    // -------------------------------------------------------------------------
#if defined(_DEBUG) || defined(METRICS)
    auto endTime{ chrono::high_resolution_clock::now() };
    cout << "metrics: \n";
    cout << "\tThread Pool Time: " << (importDictionaryTime - startTime).count() / 1000000.0f << "ms\n";
    cout << "\tTrie Import Time: " << (importTrieEndTime - importDictionaryTime).count() / 1000000.0f << "ms\n";
    cout << "\tSolver Time: " << (endTime - solverStartTime).count() / 1000000.0f << "ms\n";
    cout << "\tTotal Time: " << (endTime - startTime).count() / 1000000.0f << "ms\n";
#endif

    return 0;
}

