#include <stdio.h>

//Rotation

// https://cboard.cprogramming.com/game-programming/54048-trying-make-tetris.html

#define MAX_ROWS 21
#define MAX_COLS 14
#define MAX_BLOCKSIZE 3

typedef struct 
{
	char umBoard[MAX_ROWS][MAX_COLS];
	char uLines;
}BOARD;

typedef struct 
{
	char umBlock[MAX_BLOCKSIZE][MAX_BLOCKSIZE];
	char uX;
	char uY;
}BLOCK;

#define TRUE 1
#define FALSE 0

BOARD       g_Board = { 0 };
BLOCK       g_Block = { 0 };

//-----------------------------------------------------------------------------
//  Reset the game board
//
void ResetGameBoard()
{
	//Outer Boundary to be coevered with 1
	for (int i = 0; i < MAX_ROWS; ++i)
		for (int j = 0; j < MAX_COLS; ++j)
			if (i == 20 || j == 0 || j == 13)
				g_Board.umBoard[j][i] = 1;
			else
				g_Board.umBoard[j][i] = 0;

	g_Board.uLines = 0;
}

//-----------------------------------------------------------------------------
//  Check for a collision on the board
//
int CheckCollision(char umBlock[MAX_BLOCKSIZE][MAX_BLOCKSIZE])
{
	for (int i = 0; i < MAX_BLOCKSIZE; ++i)
	{
		for (int j = 0; j < MAX_BLOCKSIZE; ++j)
		{
			if (umBlock[j][i] == 0)
				break;
			else
				if (g_Board.umBoard[j + g_Block.uX][i + g_Block.uY] + umBlock[j][i] != umBlock[j][i])
					return TRUE;
		}
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
//  Move a block
//

int MoveBlock(int nDX, int nDY)
{
	int nTempX, nTempY;

	nTempX = g_Block.uX;
	nTempY = g_Block.uY;

	g_Block.uX += nDX;
	g_Block.uY += nDY;

#if 0
	if (TRUE == CheckCollision(g_Block.umBlock))
	{
		g_Block.uX = nTempX;
		g_Block.uY = nTempY;

		return TRUE;
	}
#endif
	return FALSE;
}


//-----------------------------------------------------------------------------
//  Rotate a block 90 degrees
//
void RotateBlock()
{
	char i, j, umFig[MAX_BLOCKSIZE][MAX_BLOCKSIZE];

	for (i = 0; i < MAX_BLOCKSIZE; ++i)
		for (j = 0; j < MAX_BLOCKSIZE; ++j)
			umFig[i][j] = g_Block.umBlock[MAX_BLOCKSIZE - j - 1][i];

#if 0
	if (TRUE == CheckCollision(umFig))
		return;
#endif

	//If no collision, then we need to copy back to original block after rotation.
	for (i = 0; i < MAX_BLOCKSIZE; ++i)
		for (j = 0; j < MAX_BLOCKSIZE; ++j)
			g_Block.umBlock[j][i] = umFig[j][i];
}


//-----------------------------------------------------------------------------
//  Insert a block
//
void InsertBlock()
{
	for (int i = 0; i < MAX_BLOCKSIZE; ++i)
	{
		for (int j = 0; j < MAX_BLOCKSIZE; ++j)
		{
			if (g_Block.umBlock[j][i] != 0)
				g_Board.umBoard[g_Block.uX + j][g_Block.uY + i] = g_Block.umBlock[j][i];
		}
	}
}

//-----------------------------------------------------------------------------
//  Remove completed lines
//
void RemoveLine(int uIndex)
{
	for (int i = uIndex; i > 0; --i)
	{
		for (int j = 1; j < MAX_COLS; ++j)
		{
			g_Board.umBoard[j][i] = g_Board.umBoard[j][i - 1];
		}
	}
}

//-----------------------------------------------------------------------------
//  Search for completed lines
//
void SearchLines()
{
	char uNumBlocks = 0;

	for (int i = 0; i < 21; ++i)
	{
		for (int j = 1; j < 13; ++j)
		{
			if (g_Board.umBoard[j][i] == 0)
			{
				uNumBlocks = 0; //if any Zero found, break and move to next line
				break;
			}
			else
			{
				++uNumBlocks;

				if (uNumBlocks >= 12)
				{
					RemoveLine(i);
					++g_Board.uLines;
					--i;
				}
			}
		}
	}
}

int main()
{
	InsertBlock();
	SearchLines();
	return 0;
}
