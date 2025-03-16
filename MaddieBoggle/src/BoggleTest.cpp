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


#include <iostream>
#include <memory>

#include "BoggleBoard.h"
#include "BoggleSolver.h"
#include "Dictionary.h"
#include "ThreadPool.h"


using namespace std;


// This value was determined through various runtime metrics. See 
// design documents folder for the metrics spreadsheet.
constexpr size_t MAX_NUM_POOL_THREADS{ 4 };

// The provided test case uses 9910 nodes. Settings to 15k just in
// case, since I don't know how this will be tested internally.
constexpr size_t DEFAULT_NODE_POOL_SIZE{ 15000 };


int main(const int argc, const char* const argv[])
{
    // extra scoping for memory profiling
    {
        // PROCESS CLI ARGS --------------------------------------------------------
        if (argc != 4)
        {
            std::cerr << "Usage: BoggleTest <dictionary_filename> <board_filename> <output_filename>" << std::endl;
            return -1;
        }

        const string dictionaryPath{ argv[1] };
        const string boardPath{ argv[2] };
        const string outputPath{ argv[3] };

        // CREATE THREAD POOL ------------------------------------------------------
        auto threadPool{ make_shared<ThreadPool>(MAX_NUM_POOL_THREADS) };

        
        // IMPORT DICTIONARY -------------------------------------------------------
        auto tempDictionary{ make_unique<Dictionary>(DEFAULT_NODE_POOL_SIZE) };
        
        auto errCode{ tempDictionary->importDictionary(dictionaryPath) };
        if (errCode != ErrorCode::SUCCESS)
        {
            return static_cast<int>(errCode);
        }
        /* Moving this to a pointer to a const object so it is thread safe. */
        shared_ptr<const Dictionary> threadSafeDictionary{ move(tempDictionary) };


        // IMPORT BOARD ------------------------------------------------------------
        BoggleBoard board{};
        errCode = importBoard(boardPath, board);
        if (errCode != ErrorCode::SUCCESS)
        {
            return static_cast<int>(errCode);
        }


        // SOLVE BOARD -------------------------------------------------------------
        auto solver{ BoggleSolver(threadSafeDictionary, threadPool, board) };
        solver.solveBoard();
        threadPool->waitForCompletion();
        solver.exportAnswers(outputPath);
    }
    // end extra memory profiling scope

    // -------------------------------------------------------------------------
    return 0;
}

