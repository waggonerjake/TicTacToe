#include <string>
#include <iostream>
#include <algorithm>

//Enums for either the player with x or o
enum boardSpot
{
	playerX, playerO
};

//Function delcartation
void selectMove(boardSpot player, std::string* board, int* validSpotsLeft);
void printBoard(std::string* board);
void checkRows(std::string currentRow, std::string nextRow, std::string lastRow, int numberOfRows, bool* winner);
void checkCols(std::string currentRow, std::string nextRow, std::string lastRow, int numberOfCols, bool* winner);
void checkDiags(std::string currentRow, std::string nextRow, std::string lastRow, int bothDiags, int position, bool* winner);

boardSpot getOpposite(boardSpot player);

bool winnerOrTie(int* validSpotsLeft, std::string* board);

///Initializes board and how many spots valid spots are in the board
//Chooses who gets to go first
int main()
{
	std::string board = "|1|2|3||4|5|6||7|8|9|";
	std::string firstMove;
	int validSpotsLeft = 9;

	std::cout << "Who will wants to go first? X or O? ";
	std::cin >> firstMove;
	
	if(firstMove == "X" || firstMove == "x")
	{
		selectMove(playerX, &board, &validSpotsLeft);
	}
	else if(firstMove == "O" || firstMove == "o")
	{
		selectMove(playerO, &board, &validSpotsLeft);
	}
	else
	{
		std::cout << "Invalid Input Detected. Making Player X Go First..." << std::endl;
		selectMove(playerX, &board, &validSpotsLeft);
	}
	
}

///Prints the dynamic board out
void printBoard(std::string* board)
{
	int boardSize = 7;
	int starter = 0;
	
	while(starter < board->length())
	{	
		for(int i = starter; i <boardSize; i++)
		{
			std::cout <<(*board)[i];
		}
		std::cout << "\n";
		starter = boardSize;
		boardSize +=boardSize;
	}
}

///Determines current player and where the player will put their character
void selectMove(boardSpot player, std::string* board, int* validSpotsLeft)
{
	if(!winnerOrTie(validSpotsLeft,board))
	{
		char currentPlayer = ((player == 0) ? 'X' : 'O');
		std::string answer;
		bool keepGoing = true;
		do
		{
			printBoard(board);
			std::cout << "Which spot would you like to place your " << currentPlayer << "?(Pick one of the valid numbers) ";
			std::cin >> answer;

			if(answer == "|" || board->find(answer) == std::string::npos)
			{
				std::cout << "Please enter a valid selection." << std::endl;
			}
			else
			{
				keepGoing = false;
			}

		}while(keepGoing);

		(*board)[board->find(answer)] = currentPlayer; 
		--(*validSpotsLeft);
		selectMove(getOpposite(player),board, validSpotsLeft);
	}
	else
	{
		printBoard(board);
	}
}

///Swaps between player x and player o by returning the opposite player
boardSpot getOpposite(boardSpot player)
{
	boardSpot opposite;
	(player == 0) ? (opposite = playerO) : (opposite = playerX);
	return opposite;
}

///Boolean function that returns whether or not the game has been 
//won or if the board is full
bool winnerOrTie(int* validSpotsLeft, std::string* board)
{
	bool gameOver = false;

	std::string firstRow = board->substr(1,6);
	std::string secondRow = board->substr(8,6);
	std::string thirdRow = board->substr(15);

	checkRows(firstRow, secondRow, thirdRow, 3, &gameOver);
	if(gameOver)
	{
		return gameOver;	
	}

	checkCols(firstRow, secondRow, thirdRow, 0, &gameOver);
	if(gameOver)
	{
		return gameOver;
	}	
	
	checkDiags(firstRow, secondRow, thirdRow, 1, 0, &gameOver);
	if(gameOver)
	{
		return gameOver;
	}

	(*validSpotsLeft > 0) ? (gameOver = false) : (gameOver = true);
        return gameOver;
}

///Checks each row of the board to see if there is a winner
void checkRows(std::string currentRow, std::string nextRow, std::string lastRow, int numberOfRows, bool* winner)
{
	int position = 0;

	if(numberOfRows > 0 || *winner)
	{
		if(currentRow[position] == 'O' && currentRow[position + 2] == 'O' && currentRow[position + 4] == 'O')
		{
			*winner = true;
		}
		else if(currentRow[position] == 'X' && currentRow[position + 2] == 'X' && currentRow[position + 4] == 'X')
		{
			*winner == true;
		}
		else
		{
			checkRows(nextRow, lastRow, currentRow, --numberOfRows, winner);
		}
	}
}		

///Checks eacg column of the board to see if there is a winner
void checkCols(std::string currentRow, std::string nextRow, std::string lastRow, int position, bool* winner)
{
	
	if(position < 5 || *winner)
	{
		if(currentRow[position] == 'O' && nextRow[position] == 'O' && lastRow[position] == 'O')
		{
			*winner = true;
		}	
		else if(currentRow[position] == 'X' && nextRow[position] == 'X' && lastRow[position] == 'X')
		{
			*winner = true;
		}
		else
		{
			checkCols(currentRow, nextRow, lastRow, position += 2, winner);
		}
	}
}

///Checks both diaganols to see if there is a winner
void checkDiags(std::string currentRow, std::string nextRow, std::string lastRow, int bothDiags, int position, bool* winner)
{
	if(bothDiags < 3 || *winner)
	{
		if(currentRow[position] == 'O' && nextRow[position += 2] == 'O' && lastRow[position += 2] == 'O')
		{
			*winner = true;
		}
		else if(currentRow[position] == 'O' && nextRow[position -= 2] == 'O' && lastRow[position -= 2] == 'O')
		{
			*winner = true;
		}
		else if(currentRow[position] == 'X' && nextRow[position += 2] == 'X' && lastRow[position += 2] == 'X')
		{
			*winner = true;
		}
		else if(currentRow[position] == 'X' && nextRow[position -= 2] == 'X' && lastRow[position -= 2] == 'X')
		{
			*winner = true;
		}
		else
		{
			checkDiags(currentRow, nextRow, lastRow, ++bothDiags, position, winner);
		}

	}
}

























