//
// Place Holder Copyright Header
//

#ifndef LETTER_NODE_POOL_H
#define LETTER_NODE_POOL_H


#include <vector>

#include "LetterNode.h"


using namespace std;


class LetterNodePool
{
public:
    LetterNodePool(size_t poolSize);
    LetterNode* allocate();
    void deallocate(LetterNode* node);

protected:
    vector<LetterNode> m_pool;          // reserved memory
    vector<LetterNode*> m_freeNodes;    // contains pointers to all the reserved memory blocks that are available for allocation
};


#endif // LETTER_NODE_POOL_H
