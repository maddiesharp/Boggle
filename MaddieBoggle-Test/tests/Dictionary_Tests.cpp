
#include "pch.h"

#include "TestDoubles.h"


TEST(Dictionary_Tests, MissingFileHandledCorrectly)
{
	// Arrange
	auto errorCode = ErrorCode::SUCCESS;
	auto dictionary = Dictionary(15000);
	string filepath = "this/path/should/not/exist.txt";

	// Act
	errorCode = dictionary.importDictionary(filepath);

	// Assert (expected, actual)
	EXPECT_EQ(ErrorCode::FILE_NOT_FOUND, errorCode);
}


TEST(Dictionary_Tests, EmptyPoolAllocatorFailsCorrectly)
{
	// Arrange
	auto dictionary = Dictionary_Double(3);

	// Act
	auto errorCode = dictionary.insertWord("abcd");

	// Assert (expected, actual)
	EXPECT_EQ(ErrorCode::OUT_OF_POOL_SPACE, errorCode);
}


TEST(Dictionary_Tests, DictionarySearchReturnsFalseWhenWordDoesntExist)
{
	// Arrange
	auto dictionary = Dictionary(150);

	// Act
	auto result = dictionary.searchDictionary("abc", SearchType::WORD);

	// Assert (expected, actual)
	EXPECT_FALSE(result);
}


TEST(Dictionary_Tests, DictionaryInsertsWordCorrectly)
{
	// Arrange
	auto dictionary = Dictionary_Double(150);
	auto root = dictionary.getRootNode();
	ASSERT_TRUE(root->m_childLetters.empty()); // root will have no children if no words added

	// set to something different so they can be checked for success
	auto status_1 = ErrorCode::OUT_OF_POOL_SPACE;

	// Act
	status_1 = dictionary.insertWord("abc");

	/*
			root
			  |
			  a
			  |
			  b
			  |
			  c
	*/

	// Assert (expected, actual)
	/* check node layout */
	EXPECT_EQ('a', root->m_childLetters[0].first);
	EXPECT_EQ('b', root->m_childLetters[0].second->m_childLetters[0].first);
	EXPECT_EQ('c', root->m_childLetters[0].second->m_childLetters[0].second->m_childLetters[0].first);

	/* check status codes */
	EXPECT_EQ(ErrorCode::SUCCESS, status_1);
}


TEST(Dictionary_Tests, MultipleWordsInsertedCorrectly)
{
	// Arrange
	auto dictionary = Dictionary_Double(150);
	auto root = dictionary.getRootNode();
	ASSERT_TRUE(root->m_childLetters.empty()); // root will have no children if no words added

	// set to something different so they can be checked for success
	auto status_1 = ErrorCode::OUT_OF_POOL_SPACE;
	auto status_2 = ErrorCode::OUT_OF_POOL_SPACE;

	// Act
	status_1 = dictionary.insertWord("abd");
	status_2 = dictionary.insertWord("abc");

	/*
			root (child vec contains 1 node - 'a')
			  |
			  a  (child vec contains 1 node - 'b')
			  |
			  b  (child vec contains 2 nodes - 'c', 'd')
			 / \
			c   d
	*/
	// Assert (expected, actual)
	/* check status codes */
	EXPECT_EQ(ErrorCode::SUCCESS, status_1);
	EXPECT_EQ(ErrorCode::SUCCESS, status_2);

	/* make sure node true contains the correct nodes */
	EXPECT_EQ('a', root->m_childLetters[0].first);
	EXPECT_EQ('b', root->m_childLetters[0].second->m_childLetters[0].first);
	EXPECT_EQ('c', root->m_childLetters[0].second->m_childLetters[0].second->m_childLetters[0].first);
	EXPECT_EQ('d', root->m_childLetters[0].second->m_childLetters[0].second->m_childLetters[1].first);

	/* check child vector sizes  */
	EXPECT_EQ(1, root->m_childLetters.size());
	EXPECT_EQ(1, root->m_childLetters[0].second->m_childLetters.size());
	EXPECT_EQ(2, root->m_childLetters[0].second->m_childLetters[0].second->m_childLetters.size());
}


TEST(Dictionary_Tests, WordsThatAreTooSmallAreNotAddedToDictionary)
{
	// Arrange
	auto dictionary = Dictionary_Double(150);
	auto root = dictionary.getRootNode();
	ASSERT_TRUE(root->m_childLetters.empty()); // root will have no children if no words added

	// set to something different so they can be checked for success
	auto status_1 = ErrorCode::OUT_OF_POOL_SPACE;

	// Act
	status_1 = dictionary.insertWord("ab"); // words less than 3 chars are not added

	// Assert (expected, actual)
	/* if word is too small, then the root won't have any children */
	EXPECT_TRUE(root->m_childLetters.empty());

	/* check status codes */
	EXPECT_EQ(ErrorCode::SUCCESS, status_1);
}


TEST(Dictionary_Tests, DictionaryCorrectlyFindsWord)
{
	// Arrange
	auto dictionary = Dictionary_Double(150);
	auto root = dictionary.getRootNode();
	ASSERT_TRUE(root->m_childLetters.empty()); // root will have no children if no words added

	bool result_1 = dictionary.searchDictionary("abc", SearchType::WORD);
	ASSERT_FALSE(result_1);

	auto status_1 = dictionary.insertWord("abc");
	ASSERT_EQ(ErrorCode::SUCCESS, status_1);

	// Act
	bool result_2 = dictionary.searchDictionary("abc", SearchType::WORD);

	// Assert (expected, actual)
	EXPECT_TRUE(result_2);
}


TEST(Dictionary_Tests, DictionaryCorrectlyIndicatesPathExistence)
{
	// Arrange
	auto dictionary = Dictionary_Double(150);
	auto root = dictionary.getRootNode();
	ASSERT_TRUE(root->m_childLetters.empty()); // root will have no children if no words added

	// Act
	dictionary.insertWord("balatro");
	bool result_1 = dictionary.searchDictionary("balay", SearchType::PATH);
	bool result_2 = dictionary.searchDictionary("balat", SearchType::PATH);

	// Assert (expected, actual)
	EXPECT_FALSE(result_1);
	EXPECT_TRUE(result_2);
}


/*
TEST(Dictionary_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
