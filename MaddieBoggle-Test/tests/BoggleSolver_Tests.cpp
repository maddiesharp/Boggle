
#include "pch.h"

#include "TestDoubles.h"


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


TEST(BoggleSolver_Tests, NoFoundWordsAtIndex)
{
	// Arrange
	/* setup dictionary with words */
	auto dictionary = make_unique<Dictionary>(1000);
	auto safeDictionary = shared_ptr<const Dictionary>(move(dictionary));
	/* setup thread pool */
	auto pool = make_shared<ThreadPool>(1);
	/* create DUT */
	BoggleSolver_Double solver(safeDictionary, pool, board);
	/* get pointer to answer set */
	auto answers = solver.getAnswers();

	// Act
	solver.findWordsPassThrough(0, 0); // no words in dictionary, so searching should find nothing

	// Assert (expected, actual)
	EXPECT_TRUE(answers->empty() == true);
}


TEST(BoggleSolver_Tests, FoundWordsAtIndex)
{
	// Arrange
	/* setup dictionary with words */
	auto dictionary = make_unique<Dictionary>(1000);
	dictionary->insertWord("pen");
	dictionary->insertWord("peg");
	auto safeDictionary = shared_ptr<const Dictionary>(move(dictionary));
	/* setup thread pool */
	auto pool = make_shared<ThreadPool>(1);
	/* create DUT */
	BoggleSolver_Double solver(safeDictionary, pool, board);
	/* get pointer to answer set */
	auto answers = solver.getAnswers();

	// Act
	solver.findWordsPassThrough(0, 0); // two words in dictionary, so searching should find them

	// Assert (expected, actual)
	/* if find call doesn't point to the end of the set, then
	the word was found */
	EXPECT_TRUE(answers->find("pen") != answers->end());
	EXPECT_TRUE(answers->find("peg") != answers->end());
}


TEST(BoggleSolver_Tests, PathExistsButItsNotAWord)
{
	// Arrange
	/* setup dictionary with words */
	auto dictionary = make_unique<Dictionary>(1000);
	dictionary->insertWord("pegolsa");
	auto safeDictionary = shared_ptr<const Dictionary>(move(dictionary));
	/* setup thread pool */
	auto pool = make_shared<ThreadPool>(1);
	/* create DUT */
	BoggleSolver_Double solver(safeDictionary, pool, board);
	/* get pointer to answer set */
	auto answers = solver.getAnswers();

	// Act
	solver.findWordsPassThrough(0, 0); 

	// Assert (expected, actual)
	/* if find call doesn't point to the end of the set, then
	the word was found */
	EXPECT_TRUE(answers->find("pegolsa") != answers->end());
	EXPECT_TRUE(answers->find("peg") == answers->end());
}


TEST(BoggleSolver_Tests, SearchOnAsymBoardWorks)
{
	// Arrange
	/* setup dictionary with words */
	auto dictionary = make_unique<Dictionary>(1000);
	dictionary->insertWord("marts");
	auto safeDictionary = shared_ptr<const Dictionary>(move(dictionary));
	/* setup thread pool */
	auto pool = make_shared<ThreadPool>(1);
	/* create DUT */
	BoggleSolver_Double solver(safeDictionary, pool, asymBoard);
	/* get pointer to answer set */
	auto answers = solver.getAnswers();

	// Act
	solver.findWordsPassThrough(1, 5); 

	// Assert (expected, actual)
	/* if find call doesn't point to the end of the set, then
	the word was found */
	EXPECT_TRUE(answers->find("marts") != answers->end());
}


TEST(BoggleSolver_Tests, QRuleSearchesForQuCorrectly)
{
	// Arrange
	/* setup dictionary with words */
	auto dictionary = make_unique<Dictionary>(1000);
	dictionary->insertWord("quit");
	auto safeDictionary = shared_ptr<const Dictionary>(move(dictionary));
	/* setup thread pool */
	auto pool = make_shared<ThreadPool>(1);
	/* create DUT */
	BoggleSolver_Double solver(safeDictionary, pool, asymBoard);
	/* get pointer to answer set */
	auto answers = solver.getAnswers();

	// Act
	solver.findWordsPassThrough(2, 3); 

	// Assert (expected, actual)
	/* if find call doesn't point to the end of the set, then
	the word was found */
	EXPECT_TRUE(answers->find("quit") != answers->end());
}


/*
TEST(BoggleSolver_Tests, )
{
	// Arrange


	// Act


	// Assert (expected, actual)

}
*/
