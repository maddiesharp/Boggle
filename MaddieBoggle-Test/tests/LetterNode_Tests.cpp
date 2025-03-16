#include "pch.h"

TEST(LetterNode_Tests, CantFindMissingChild)
{
	// Arrange
	auto node_1 = LetterNode();

	// Act
	ASSERT_TRUE(node_1.m_childLetters.empty());
	auto node_2 = node_1.findChild('d');

	// Assert (expected, actual)
	EXPECT_TRUE(node_2 == nullptr);
}


TEST(LetterNode_Tests, AddChildToEmptyPool)
{
	// Arrange
	auto node_1 = LetterNode();
	auto node_2 = LetterNode();
	char letter = 'd';

	// Act
	ASSERT_TRUE(node_1.m_childLetters.empty());
	node_1.insertChild(letter, &node_2);

	// Assert (expected, actual)
	EXPECT_EQ(1, node_1.m_childLetters.size());
	EXPECT_EQ(letter, node_1.m_childLetters[0].first);
}


TEST(LetterNode_Tests, GetChildIfItExists)
{
	// Arrange
	auto node_1 = LetterNode();
	auto node_2 = LetterNode();

	node_2.m_childLetters.emplace_back('c', nullptr); // give node_2 a "node" assigned to the char 'c'
	char letter = 'd';

	ASSERT_TRUE(node_1.m_childLetters.empty());
	node_1.insertChild(letter, &node_2);			  // now give node_1 a pair of char 'd' assigned to node_2	

	// Act
	auto node_3 = node_1.findChild(letter);           // the node 3 we got should actually be node 2

	// Assert (expected, actual)
	EXPECT_EQ('c', node_3->m_childLetters[0].first);
}


TEST(LetterNode_Tests, ChildrenRemainInAscendingOrderWhenAdded)
{
	// Arrange Act
	auto node_1 = LetterNode();
	auto node_2 = LetterNode();
	auto node_3 = LetterNode();
	auto node_4 = LetterNode();
	
	/* Test Progression
			   			  Act 1                Act 2                         Act 3
			node_1       node_1				  node_1					    node_1
							|				/		\				  /       |	      \
						{d,node_2}    {c,node_3}  {d,node_2}	{c,node_3}{d,node_2}{e,node_4}
	*/

	// Act 1 - first node should be assigned to 'd' since it's the only one
	ASSERT_TRUE(node_1.m_childLetters.empty());
	node_1.insertChild('d', &node_2);
	ASSERT_TRUE(node_1.m_childLetters.size() == 1);
	
	// Assert (expected, actual)
	EXPECT_EQ('d', node_1.m_childLetters[0].first);


	// Act 2 - first node should be assigned to 'c' since it's comes before 'd', even though
	// it was added afterwards
	node_1.insertChild('c', &node_3);
	ASSERT_TRUE(node_1.m_childLetters.size() == 2);

	// Assert (expected, actual)
	EXPECT_EQ('c', node_1.m_childLetters[0].first);
	EXPECT_EQ('d', node_1.m_childLetters[1].first);


	// Act 3 - 'e' should be added at the end since it comes after 'c' and 'd'
	node_1.insertChild('e', &node_3);
	ASSERT_TRUE(node_1.m_childLetters.size() == 3);

	// Assert (expected, actual)
	EXPECT_EQ('c', node_1.m_childLetters[0].first);
	EXPECT_EQ('d', node_1.m_childLetters[1].first);
	EXPECT_EQ('e', node_1.m_childLetters[2].first);
}


TEST(LetterNode_Tests, DuplicateChildrenAreNotAdded)
{
	// Arrange
	auto node_1 = LetterNode();
	
	auto node_2 = LetterNode();
	node_2.m_childLetters.emplace_back('f', nullptr); // node 2 given an f in its vector
	
	auto node_3 = LetterNode();
	node_3.m_childLetters.emplace_back('g', nullptr); // node 3 given a g in its vector

	// Act
	ASSERT_TRUE(node_1.m_childLetters.empty());
	node_1.insertChild('d', &node_2);
	node_1.insertChild('d', &node_3);

	// Assert (expected, actual)
	EXPECT_EQ(1, node_1.m_childLetters.size());		// node_3 won't be added because 'd' is a duplicate
	EXPECT_EQ('f', node_1.m_childLetters[0].second->m_childLetters[0].first); // the one node in here will be node 2 with an assigned 'f' char
}


/*
TEST(LetterNode_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
