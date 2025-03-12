// MaddieBoggle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>


#include "WordTrie.h"


int main()
{
    {   
        WordTrie dictionary{};
        int errCode{ dictionary.importDictionary("../supplementary/dictionary.txt") };
        if (errCode > 0)
        {
            return errCode;
        }


    } // scoping to test node destuctors

#ifdef _DEBUG
    cout << "maddie boggle\n";
    cout << "metrics:\nnode count: " << nodeCount << "\nkill count: " << killCount << endl;
#endif

    return 0;
}


