
#include "pch.h"

TEST(BoggleBoard_Tests, MissingFileHandledCorrectly) 
{
	// Arrange
	auto errorCode = ErrorCode::SUCCESS;
	BoggleBoard board{};
	string filepath = "this/path/should/not/exist.txt";

	// Act
	errorCode = importBoard(filepath, board);

	// Assert (expected, actual)
	EXPECT_EQ(ErrorCode::FILE_NOT_FOUND, errorCode);
}


/* 
TEST(BoggleBoard_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
