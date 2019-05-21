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



	int suduko[ROWS][COLS] = 
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


	int parSuduko[ROWS][COLS] =
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



	playSudoku(suduko);



	system("pause");
	return 0;
}

void playSudoku(int array[ROWS][COLS])
{
	bool flag = false; // Prove puzzle is complete

	while (!flag)
	{
		for (int x = 0; x < ROWS; x++)
		{
			for (int y = 0; x < ROWS; y++)
			{
				if (array[x][y] == 0)
				{
					flag = false; // puzzle is still not complete
				}
			}
		}

		if (!flag) // puzzle is not complete, so commence a crosshatch cycle (9 iterations)
		{
			for (int x = 1; x < 9 + 1; x++)
			{
				crossHatchMarker(array, x);
			}
		}
		else // puzzle is complete
		{
			flag = true;
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


	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			if (array[x][y] != 0)
			{
				parSudoku[x][y] == 1; // Marked taken spot
			}
		}
	}


	// Mark Parallel columns and Perpendicular Rows to the number we are searching for when an instance is found
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			if (array[x][y] == num)
			{
				for (int z = 0; z < x; z++) // Mark col up to x
				{
					parSudoku[z][y] == 1;
				}
				for (int z = x; z < ROWS; z++) // Mark col after x
				{
					parSudoku[z][y] == 1;
				}
				for (int z = 0; z < ROWS; z++) // Mark row up to y
				{

				}
				for (int z = 0; z < ROWS; z++) // Mark row after y
				{

				}
			}
		}
	}


	crossHatchPlacer(parSudoku, array);
}

void crossHatchPlacer(int array[ROWS][COLS], int sudokuArray[ROWS][COLS], int num)
{
}
