//
// Place Holder Copyright Header
//

#include <cassert>
#include <iostream>

#include "LetterNodePool.h"


/// <summary>
/// Class constructor. Provided size must be greater than 0.
/// </summary>
/// <param name="poolSize">number of node objects to reserve on the heap</param>
LetterNodePool::LetterNodePool(size_t poolSize)
{
    assert(poolSize > 0);
    m_pool.reserve(poolSize); // ensures the pool vector doesn't dynamically resize

    for (size_t i = 0; i < poolSize; ++i)
    {
        /* create a node object on the pool and get its reference, then
        take the newly created reference and add its address to the available
        nodes list */
        LetterNode& node{ m_pool.emplace_back() };
        m_freeNodes.push_back(&node);
    }
}


/// <summary>
/// Allocates a node by returning the next available address of one.
/// If there are no more allocatable nodes, return nullptr. Callee is
/// responsible for handling.
/// Allocated node is removed from the free pool.
/// </summary>
/// <returns>Pointer to available node, otherwise nullptr</returns>
LetterNode* LetterNodePool::allocate()
{
    if (m_freeNodes.empty())
    {
        cerr << "Out of allocation space! Dictionary too large.\n";
        return nullptr;
    }

    auto node{ m_freeNodes.back() };    // get a free node address
    m_freeNodes.pop_back();             // remove acquired node address from the free nodes
    return node;
}


/// <summary>
/// Puts a deleted node back into the allocation pool.
/// </summary>
/// <param name="node">Node address to reallocate.</param>
void LetterNodePool::deallocate(LetterNode* node)
{
    m_freeNodes.push_back(node);
}
