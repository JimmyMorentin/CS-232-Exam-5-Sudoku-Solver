#include <iostream>
#include <string>

using namespace std;

const int ROWS = 9;
const int COLS = 9;

void playSudoku(int array[ROWS][COLS]);

void crossHatchMarker(int array[ROWS][COLS], int num);

void crossHatchPlacer(int array[ROWS][COLS], int sudokuArray[ROWS][COLS], int num);

int main()
{
	int sudoku[ROWS][COLS] = 
	{
		{5, 3, 4, 0, 7, 0, 9, 1, 2},
		{6, 0, 0, 1, 9, 5, 0, 0, 8},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 4},
		{2, 7, 8, 4, 1, 9, 0, 0, 5},
		{3, 4, 5, 0, 8, 0, 0, 7, 9}
	};




	playSudoku(sudoku);

	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			cout << sudoku[x][y] << " ";
		}
		cout << endl;
	}


	system("pause");
	return 0;
}

void playSudoku(int array[ROWS][COLS])
{
	int counter = 0; // TAG
	bool flag = false; // Prove puzzle is complete

	while (!flag) // While there are still blank spaces, cross hatch!
	{
		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; y < COLS; y++)
			{
				if (array[x][y] == 0)
				{
					flag = false; // puzzle is still not complete
					for (int x = 1; x < 9 + 1; x++)
					{
						crossHatchMarker(array, x);
						counter++;
					}
					
				}
				else if (x + 1 == ROWS && y + 1 == COLS && array[x][y] != 0)
				{
					flag = true; // finished
					cout << "EXECUTED: " << counter << " times" << endl; // TAG
				}
			}
		}
	}
	
	
}

void crossHatchMarker(int array[ROWS][COLS], int num)
{

	int parSudoku[ROWS][COLS] = 
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};


	for (int x = 0; x < ROWS; x++) // Searches for spots already taken by other numbers and marks them
	{
		for (int y = 0; y < COLS; y++)
		{
			if (array[x][y] != 0)
			{
				parSudoku[x][y] = 1; // Marked taken spot
			}
		}
	}

	// Mark Parallel columns and Perpendicular Rows to the number we are searching for when an instance is found
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			if (array[x][y] == num) // ROW: [x][0-9] COL: [0-9][y]
			{
				for (int z = 0; z < ROWS; z++) // Mark col 
				{
					parSudoku[z][y] = 1;
				}
				for (int z = 0; z < COLS; z++) // Mark row
				{
					parSudoku[x][z] = 1;
				}
			}
		}
	}
	crossHatchPlacer(parSudoku, array, num);
}

void crossHatchPlacer(int array[ROWS][COLS], int sudokuArray[ROWS][COLS], int num)
{
	// Check If there are any spots for our number first
	bool finished = false;
	
	int xpos;
	int ypos;

	do
	{
		bool flag = false;
		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; y < COLS; y++)
			{
				if (array[x][y] == 0)
				{
					flag = true;
					xpos = x;
					ypos = y;
					break;
				}
				else if (x + 1 == ROWS && y + 1 == COLS && array[x][y] != 0)
				{
					finished = true;
				}
			}
			if (flag == true)
			{
				break; // Break out of second for loop
			}
		}

		if (flag) // Open space is available somewhere for our number
		{
			// Check the subgrid we are in for duplicates

			if (xpos <= 2 && ypos <= 2) // First subgrid
			{
				bool duplicate = false; // Prove there is a duplicate
				for (int k = 0; k < 2 + 1; k++)
				{
					for (int l = 0; l < 2 + 1; l++)
					{
						if (sudokuArray[k][l] == num) // Duplicate found
						{
							duplicate = true;
						}
					}
				}

				if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
				{
					sudokuArray[xpos][ypos] == num;
					array[xpos][ypos] == 1; // Update parArray

				}

			}
			else if (xpos <= 2 && 3 <= ypos && ypos <= 5) // Second subgrid
			{
				bool duplicate = false; // Prove there is a duplicate
				for (int k = 0; k < 2 + 1; k++)
				{
					for (int l = 3; l < 5 + 1; l++)
					{
						if (sudokuArray[k][l] == num) // Duplicate found
						{
							duplicate = true;
						}
					}
				}

				if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
				{
					sudokuArray[xpos][ypos] == num;
					array[xpos][ypos] == 1; // Update parArray
				}

			}
			else if (xpos <= 2 && 6 <= ypos && ypos <= 8) // Third subgrid
			{
				bool duplicate = false; // Prove there is a duplicate
				for (int k = 0; k < 2 + 1; k++)
				{
					for (int l = 6; l < 8 + 1; l++)
					{
						if (sudokuArray[k][l] == num) // Duplicate found
						{
							duplicate = true;
						}
					}
				}

				if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
				{
					sudokuArray[xpos][ypos] == num;
					array[xpos][ypos] == 1; // Update parArray
				}

			}
			else if (3 <= xpos && xpos <= 5 && ypos < 2) // Fourth subgrid
			{
				bool duplicate = false; // Prove there is a duplicate
				for (int k = 3; k < 5 + 1; k++)
				{
					for (int l = 0; l < 2 + 1; l++)
					{
						if (sudokuArray[k][l] == num) // Duplicate found
						{
							duplicate = true;
						}
					}
				}

				if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
				{
					sudokuArray[xpos][ypos] == num;
					array[xpos][ypos] == 1; // Update parArray
				}

			}
			else if (3 <= xpos && xpos <= 5 && 3 <= ypos && ypos <= 5) // Fifth subgrid
			{
				bool duplicate = false; // Prove there is a duplicate
				for (int k = 3; k < 5 + 1; k++)
				{
					for (int l = 3; l < 5 + 1; l++)
					{
						if (sudokuArray[k][l] == num) // Duplicate found
						{
							duplicate = true;
						}
					}
				}

				if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
				{
					sudokuArray[xpos][ypos] == num;
					array[xpos][ypos] == 1; // Update parArray
				}

			}
			else if (3 <= xpos && xpos <= 5 && 6 <= ypos && ypos <= 8) // Sixth subgrid
			{
			bool duplicate = false; // Prove there is a duplicate
			for (int k = 3; k < 5 + 1; k++)
			{
				for (int l = 6; l < 8 + 1; l++)
				{
					if (sudokuArray[k][l] == num) // Duplicate found
					{
						duplicate = true;
					}
				}
			}

			if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
			{
				sudokuArray[xpos][ypos] == num;
				array[xpos][ypos] == 1; // Update parArray
			}

			}
			else if (6 <= xpos && xpos <= 8 && ypos < 2) // Seventh subgrid [6-8][0-2]
			{
			bool duplicate = false; // Prove there is a duplicate
			for (int k = 6; k < 8 + 1; k++)
			{
				for (int l = 0; l < 2 + 1; l++)
				{
					if (sudokuArray[k][l] == num) // Duplicate found
					{
						duplicate = true;
					}
				}
			}

			if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
			{
				sudokuArray[xpos][ypos] == num;
				array[xpos][ypos] == 1; // Update parArray
			}

			}
			else if (6 <= xpos && xpos <= 8 && 3 <= ypos <= 5) // Eigth subgrid [6-8][3-5]
			{
			bool duplicate = false; // Prove there is a duplicate
			for (int k = 6; k < 8 + 1; k++)
			{
				for (int l = 3; l < 5 + 1; l++)
				{
					if (sudokuArray[k][l] == num) // Duplicate found
					{
						duplicate = true;
					}
				}
			}

			if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
			{
				sudokuArray[xpos][ypos] == num;
				array[xpos][ypos] == 1; // Update parArray
			}

			}
			else if (6 <= xpos && xpos <= 8 && 6 <= ypos <= 8) // Ninth subgrid [6-8][6-8]
			{
			bool duplicate = false; // Prove there is a duplicate
			for (int k = 6; k < 8 + 1; k++)
			{
				for (int l = 6; l < 8 + 1; l++)
				{
					if (sudokuArray[k][l] == num) // Duplicate found
					{
						duplicate = true;
					}
				}
			}

			if (!duplicate) // If there is not a duplicate, good to go for our num to be placed there
			{
				sudokuArray[xpos][ypos] == num;
				array[xpos][ypos] == 1; // Update parArray
			}

			}

		}
		else
		{
			return; // No available space
		}
		
	} while (!finished);
}
