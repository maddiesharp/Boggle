//
// Place Holder Copyright Header
//

#ifndef BOGGLE_BOARD_H
#define BOGGLE_BOARD_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ErrorCodes.h"


using namespace std;
using BoggleBoard = vector<vector<char>>; // alias for 2d data structure to store boggle characters


/// <summary>
/// This function loads the boggle board from the provided file system path and
/// stores it into the provided vector<vector<char>>& to be used by other entities.
/// 
/// Only alphabetical characters 'a'-'z' are importing. 'A'-'Z' will be converted to
/// lowercase, while all other ascii chars will be ignored. Empty lines are skipped.
/// 
/// NOTE - As a feature, asymetrical boggle boards are accepted into the board. They
/// can be parsed accordingly by the designated traversal functions (see IndexSolverHelper.h).
/// 
/// The following error codes can be returned:
/// 0 --> success, no error
/// 1 --> unable to open file
/// 2 --> unprecendented error saved by a try-catch block, error is not identified, 
///     so the callee should exit gracefully
/// </summary>
/// <param name="filepath">string filepath to load the boggle board from</param>
/// <param name="board">vector of vector<char>& to load the board from the file into</param>
/// <returns>enum class error code (0 = success)</returns>
static ErrorCode importBoard(const string& filepath, BoggleBoard& board)
{
    try
    {
        ifstream file(filepath);
        if (!file)
        {
            cerr << "Error finding file at path: " << filepath << ".\n";
            return ErrorCode::FILE_NOT_FOUND;
        }
       
        string line{};
        while (getline(file, line)) // import line of chars
        {
            vector<char> tempVec{};
            for (const auto& c : line)
            {

                // only add letters 'A'-'Z' and 'a'-'z'
                const auto lowerC{ static_cast<char>(tolower(c)) };
                if ((lowerC >= 'a') && (lowerC <= 'z'))
                {
                    tempVec.push_back(lowerC);
                }
            }

            // ignore empty lines
            if (!tempVec.empty())
            {
                board.push_back(tempVec);
            }
        }

        file.close();
        return ErrorCode::SUCCESS;
    }
    catch (...)
    {
        cerr << "Unexpected error when importing board file!\n";
        return ErrorCode::UNKNOWN_FILE_ERR;
    }
}


#endif // BOGGLE_BOARD_H
