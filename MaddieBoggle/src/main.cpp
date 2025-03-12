
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


constexpr size_t DEFAULT_NODE_POOL_SIZE{ 20000 };


int main(const int argc, const char* const argv[])
{
    // extra scoping for memory profiling
    {
        // PROCESS CLI ARGS --------------------------------------------------------
        if (argc != 4)
        {
            std::cerr << "Usage: MaddieBoggle <dictionary_filename> <board_filename> <output_filename>" << std::endl;
            return -1;
        }

        cout << "Maddie Boggle\n"; // sanity print

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

