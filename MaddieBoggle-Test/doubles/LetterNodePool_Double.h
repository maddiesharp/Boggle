
#include "LetterNodePool.h"

class LetterNodePool_Double : public LetterNodePool
{
public:
	LetterNodePool_Double(size_t poolSize) :
		LetterNodePool(poolSize)
	{

	}

	size_t getPoolSize() { return m_pool.size(); }
	size_t getFreeNodesLeft() { return m_freeNodes.size(); }
};
