
#include "pch.h"

#include "LetterNodePool_Double.h"

TEST(Dictionary_Tests, MissingFileHandledCorrectly)
{
	// Arrange
	auto errorCode = 0;
	auto dictionary = Dictionary(15000);
	string filepath = "this/path/should/not/exist.txt";

	// Act
	errorCode = dictionary.importDictionary(filepath);

	// Assert (expected, actual)
	EXPECT_EQ(1, errorCode);
}


/*
TEST(Dictionary_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/