
#include "pch.h"

TEST(BoggleBoard_Tests, MissingFileHandledCorrectly) 
{
	// Arrange
	auto errorCode = 0;
	BoggleBoard board{};
	string filepath = "this/path/should/not/exist.txt";

	// Act
	errorCode = importBoard(filepath, board);

	// Assert (expected, actual)
	EXPECT_EQ(1, errorCode);
}


/* 
TEST(BoggleBoard_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
