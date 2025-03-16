
#include "pch.h"


const vector<vector<char>> board{
	{'p','w','y','r'}, /* 0,0 - 0,1 - 0,2 - 0,3  */
	{'e','n','t','h'}, /* 1,0 - 1,1 - 1,2 - 1,3  */
	{'g','s','i','q'}, /* 2,0 - 2,1 - 2,2 - 2,3  */
	{'o','l','s','a'}  /* 3,0 - 3,1 - 3,2 - 3,3  */
};

const vector<vector<char>> asymBoard{
	{'p','w','y','r','a'},		/* 0,0 - 0,1 - 0,2 - 0,3 - 0,4        */
	{'e','n','t','h','e','m'},  /* 1,0 - 1,1 - 1,2 - 1,3 - 1,4 - 1,5  */
	{'g','s','i','q'},			/* 2,0 - 2,1 - 2,2 - 2,3              */
	{'o','l','s','a','m'}		/* 3,0 - 3,1 - 3,2 - 3,3 - 3,4        */
};

// up tests
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUp_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUp(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 0,1 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUp_NodeOutOfIndex)
{
	// Arrange
	size_t row = 0;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUp(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUp_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {0,1} };

	// Act
	checkNodeUp(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


// down tests
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDown_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeDown(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 2,1 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDown_NodeOutOfIndex)
{
	// Arrange
	size_t row = 3;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeDown(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDown_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {2,1} };

	// Act
	checkNodeDown(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


// right tests
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeRight_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 1,2 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeRight_NodeOutOfIndex)
{
	// Arrange
	size_t row = 1;
	size_t col = 3;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeRight_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {1,2} };

	// Act
	checkNodeRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


// left tests
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeLeft_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeLeft(row, col, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 1,0 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeLeft_NodeOutOfIndex)
{
	// Arrange
	size_t row = 1;
	size_t col = 0;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeLeft(row, col, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}



TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeLeft_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {1,0} };

	// Act
	checkNodeLeft(row, col, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


// up left tests
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUpLeft_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpLeft(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 0,0 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUpLeft_NodeOutOfIndex)
{
	// Arrange
	size_t row = 1;
	size_t col = 0;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpLeft(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUpLeft_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {0,0} };

	// Act
	checkNodeUpLeft(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


/* 0,0 - 0,1 - 0,2 - 0,3 - 0,4        */
/* 1,0 - 1,1 - 1,2 - 1,3 - 1,4 - 1,5  */
/* 2,0 - 2,1 - 2,2 - 2,3              */
/* 3,0 - 3,1 - 3,2 - 3,3 - 3,4        */
TEST(BoggleSolverHelper_Tests, AsymBoard_CheckNodeUpLeft_AsymNodeExists)
{
	// Arrange
	size_t row = 1;
	size_t col = 5;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpLeft(row, col, asymBoard, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 0,4 }) != validNodes.end());
}


// up right
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUpRight_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 0,2 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUpRight_NodeOutOfIndex)
{
	// Arrange
	size_t row = 1;
	size_t col = 3;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeUpRight_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {0,2} };

	// Act
	checkNodeUpRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


/* 0,0 - 0,1 - 0,2 - 0,3 - 0,4        */
/* 1,0 - 1,1 - 1,2 - 1,3 - 1,4 - 1,5  */
/* 2,0 - 2,1 - 2,2 - 2,3              */
/* 3,0 - 3,1 - 3,2 - 3,3 - 3,4        */
TEST(BoggleSolverHelper_Tests, AsymBoard_CheckNodeUpRight_AsymNodeExists)
{
	// Arrange
	size_t row = 2;
	size_t col = 3;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpRight(row, col, asymBoard, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 1,4 }) != validNodes.end());
}


// down right
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDownRight_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 0,2 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDownRight_NodeOutOfIndex)
{
	// Arrange
	size_t row = 1;
	size_t col = 3;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeUpRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDownRight_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {0,2} };

	// Act
	checkNodeUpRight(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


// down left
TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDownLeft_NodeValid)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeDownLeft(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.find({ 2,0 }) != validNodes.end());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDownLeft_NodeOutOfIndex)
{
	// Arrange
	size_t row = 1;
	size_t col = 0;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{};

	// Act
	checkNodeDownLeft(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


TEST(BoggleSolverHelper_Tests, NormalBoard_CheckNodeDownLeft_NodeAlreadyVisited)
{
	// Arrange
	size_t row = 1;
	size_t col = 1;
	BoggleSolver::BoardNodes validNodes{};
	BoggleSolver::BoardNodes visitNodes{ {2,0} };

	// Act
	checkNodeDownLeft(row, col, board, validNodes, visitNodes);

	// Assert (expected, actual)
	EXPECT_TRUE(validNodes.empty());
}


/*
TEST(BoggleSolverHelper_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
