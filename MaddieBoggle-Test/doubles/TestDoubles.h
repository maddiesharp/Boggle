
#include "LetterNodePool.h"
#include "Dictionary.h"

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


class Dictionary_Double : public Dictionary
{
public:
	Dictionary_Double(size_t poolSize) :
		Dictionary(poolSize)
	{

	}

	LetterNode* getRootNode()		{ return m_root;  }
	LetterNodePool* getPoolRef()	{ return &m_pool; }
};


