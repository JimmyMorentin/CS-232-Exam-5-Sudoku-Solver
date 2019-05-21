#include <iostream>
#include <string>

using namespace std;

const int ROWS = 9;
const int COLS = 9;

void playSudoku(int sudokuArray[ROWS][COLS]);

void crossHatchMarker(int sudokuArray[ROWS][COLS], int num);

void crossHatchPlacer(int parArray[ROWS][COLS], int sudokuArray[ROWS][COLS], int num, int xpos, int ypos);

void subGridAnalyzer(int parArray[ROWS][COLS], int sudokuArray[ROWS][COLS], int num, int xLower, int xUpper, int yLower, int yUpper, int xpos, int ypos);

void placeNum(int parArray[ROWS][COLS], int sudokuArray[ROWS][COLS], int num, int xpos, int ypos);

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
		{2, 0, 7, 4, 1, 9, 0, 0, 5},
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
// REAL FUNCTION
/*void playSudoku(int sudokuArray[ROWS][COLS])
{
	
	bool flag = false; // Prove puzzle is complete

	while (!flag) // While there are still blank spaces, cross hatch!
	{
		int counter = 0; // TAG
		for (int x = 0; x < ROWS; x++) // Check for empty spaces, represented by a zero
		{
			for (int y = 0; y < COLS; y++)
			{
				if (sudokuArray[x][y] == 0)
				{
					counter++;
				}
			}
		}
		cout << counter << endl; // TAG zeroes left
		if (counter != 0) // If there are blank spaces
		{
			for (int z = 1; z < 9 + 1; z++)
			{
				crossHatchMarker(sudokuArray, z);
			}
		}
		else if(counter == 0) // No more blank spaces
		{
			flag = true;
		}
	}
	
	
}*/

void playSudoku(int sudokuArray[ROWS][COLS])
{
	int counter = 0; // TAG
	bool flag = false; // Prove puzzle is complete

	while (!flag) // While there are still blank spaces, cross hatch!
	{
		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; y < COLS; y++)
			{
				if (sudokuArray[x][y] == 0)
				{
					flag = false; // puzzle is still not complete
					for (int x = 1; x < 9 + 1; x++)
					{
						crossHatchMarker(sudokuArray, x);
						counter++;
					}

				}
				else if (x + 1 == ROWS && y + 1 == COLS && sudokuArray[x][y] != 0)
				{
					flag = true; // finished
					cout << "EXECUTED: " << counter << " times" << endl; // TAG
				}
			}
		}
	}


}

void crossHatchMarker(int sudokuArray[ROWS][COLS], int num)
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
			if (sudokuArray[x][y] != 0)
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
			if (sudokuArray[x][y] == num) // ROW: [x][0-9] COL: [0-9][y]
			{
				cout << "NUM FOUND IN ROW: " << x << "AND COL: " << y << endl;
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

	cout << endl;

		// Prints Sudoku grid
		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; y < COLS; y++)
			{
				cout << sudokuArray[x][y] << " ";
			}
			cout << endl;
		}

	// Search for open spaces to place our number
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			if (parSudoku[x][y] == 0)
			{
				crossHatchPlacer(parSudoku, sudokuArray, num, x, y); // If successful, places our number in the pos (x, y)
			}
		}
	}
	
}

void crossHatchPlacer(int parArray[ROWS][COLS], int sudokuArray[ROWS][COLS], int num, int xpos, int ypos)
{
						// Check the subgrid we are in for duplicates
	
						if (0 <= xpos && xpos <= 2 && 0 <= ypos && ypos <= 2) // First subgrid [0-2][0-2]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 0, 2, 0, 2, xpos, ypos);
						}
						else if (0 <= xpos && xpos <= 2 && 3 <= ypos && ypos <= 5) // Second subgrid [0-2][3-5]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 0, 2, 3, 5, xpos, ypos);
						}
						else if (0 <= xpos && xpos <= 2 && 6 <= ypos && ypos <= 8) // Third subgrid [0-2][6-8]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 0, 2, 6, 8, xpos, ypos);
						}
						else if (3 <= xpos && xpos <= 5 && 0 <= ypos && ypos <= 2) // Fourth subgrid [3-5][0-2]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 3, 5, 0, 2, xpos, ypos);
						}
						else if (3 <= xpos && xpos <= 5 && 3 <= ypos && ypos <= 5) // Fifth subgrid [3-5][3-5]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 3, 5, 3, 5, xpos, ypos);
						}
						else if (3 <= xpos && xpos <= 5 && 6 <= ypos && ypos <= 8) // Sixth subgrid [3-5][6-8]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 3, 5, 6, 8, xpos, ypos);
						}
						else if (6 <= xpos && xpos <= 8 && 0 <= ypos && ypos <= 2) // Seventh subgrid [6-8][0-2]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 6, 8, 0, 2, xpos, ypos);
						}
						else if (6 <= xpos && xpos <= 8 && 3 <= ypos && ypos <= 5) // Eigth subgrid [6-8][3-5]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 6, 8, 3, 5, xpos, ypos);
						}
						else if (6 <= xpos && xpos <= 8 && 6 <= ypos && ypos <= 8) // Ninth subgrid [6-8][6-8]
						{
							subGridAnalyzer(parArray, sudokuArray, num, 6, 8, 6, 8, xpos, ypos);
						}
}

void subGridAnalyzer(int parArray[ROWS][COLS], int sudokuArray[ROWS][COLS], int num, int xLower, int xUpper, int yLower, int yUpper, int xpos, int ypos)
{
	//cout << "In subgrid: [" << xLower << "-" << xUpper << "][" << yLower << "-" << yUpper << "]" << endl << endl;
						int openSpace = 0; // Must be 1 for a number to be placed
						bool duplicate = false; // Prove there is a duplicate
						for (int k = xLower; k < (xUpper + 1); k++)
						{
							for (int l = yLower; l < (yUpper + 1); l++)
							{
								if (parArray[k][l] == 0)
								{
									openSpace += 1;
									//cout << "POTENTIAL OPEN SPACE!" << endl;
									//cout << "PAR Sudoku box: " << "k: " << k << " l: " << l << " holds: " << sudokuArray[k][l] << endl;
								}
								//cout << "Sudoku box: " << "k: " << k << " l: " << l << " holds: " << sudokuArray[k][l] << endl;
								if (sudokuArray[k][l] == num) // Duplicate found
								{
									duplicate = true;
								}

								//cout << parArray[k][l] << " "; // TAG

							}
							//cout << endl; // TAG
						}

						if (duplicate) // TAG
						{
							// cout << "Duplicate found!" << endl;
						}

						if (!duplicate && parArray[xpos][ypos] != 1 && openSpace == 1) // If there is not a duplicate, good to go for our num to be placed there
						{
							placeNum(parArray, sudokuArray, num, xpos, ypos);
							cout << "****" << endl;
						}

						
}

void placeNum(int parArray[ROWS][COLS], int sudokuArray[ROWS][COLS], int num, int xpos, int ypos)
{
	sudokuArray[xpos][ypos] = num;

	// Update parArray




	cout << "Num: " << num << " placed @ " << "(" << xpos << ", " << ypos << ")" << endl;
//	cout << "PAR ARRAY @ (" << xpos << ", " << ypos << ") is: " << parArray[xpos][ypos]<< endl;
}
