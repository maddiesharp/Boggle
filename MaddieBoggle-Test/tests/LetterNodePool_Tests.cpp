
#include "pch.h"

#include "TestDoubles.h"

TEST(LetterNodePool_Tests, PoolIsAllocatedToExpectedSize)
{
	// Arrange
	size_t poolSize = 10;

	// Act
	auto pool = LetterNodePool_Double(poolSize);

	// Assert (expected, actual)
	EXPECT_EQ(10, pool.getPoolSize());
	EXPECT_EQ(10, pool.getFreeNodesLeft());
}


TEST(LetterNodePool_Tests, AllocatedNodeRemovesFreeNode)
{
	// Arrange
	size_t poolSize = 10;
	auto pool = LetterNodePool_Double(poolSize);
	ASSERT_EQ(10, pool.getPoolSize());
	ASSERT_EQ(10, pool.getFreeNodesLeft());

	// Act
	auto node = pool.allocate(); // get 1 node from the pool

	// Assert (expected, actual)
	EXPECT_EQ(9, pool.getFreeNodesLeft());
	EXPECT_NE(node, nullptr);
}


TEST(LetterNodePool_Tests, NodesGetDeallocatedCorrectly)
{
	// Arrange
	size_t poolSize = 10;
	auto pool = LetterNodePool_Double(poolSize);
	ASSERT_EQ(10, pool.getPoolSize());
	ASSERT_EQ(10, pool.getFreeNodesLeft());

	auto node = pool.allocate(); // get 1 node from the pool
	ASSERT_EQ(9, pool.getFreeNodesLeft());
	ASSERT_NE(node, nullptr);

	// Act
	pool.deallocate(node);

	// Assert (expected, actual)
	EXPECT_EQ(10, pool.getFreeNodesLeft());
}


TEST(LetterNodePool_Tests, PoolReturnsNullPointerWhenOutOfFreeSpace)
{
	// Arrange
	size_t poolSize = 1;
	auto pool = LetterNodePool_Double(poolSize);
	ASSERT_EQ(1, pool.getPoolSize());
	ASSERT_EQ(1, pool.getFreeNodesLeft());

	auto node_1 = pool.allocate(); // get 1 node from the pool
	ASSERT_EQ(0, pool.getFreeNodesLeft());

	// Act
	auto node_2 = pool.allocate(); // get 1 node from the pool

	// Assert (expected, actual)
	EXPECT_EQ(nullptr, node_2);
}


/*
TEST(LetterNodePool_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
