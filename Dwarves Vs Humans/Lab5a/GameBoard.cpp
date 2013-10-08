#include "GameBoard.h"
#include "WindowsSprite.h"
#include "WindowsInput.h"
#include <math.h>
#include "Cell.h"

GameBoard::GameBoard(void)
{
}


GameBoard::~GameBoard(void)
{
}

void GameBoard::handleClicks(WindowsInput input)
{
	//set the end marker
	if((input.rightButtonDown == true) && (input.keys[VK_SHIFT] == false))
	{
		if((input.mouseX < boardWidth * defaultCell.cellSprite.width) && (input.mouseY < boardHeight * defaultCell.cellSprite.height)){
			setEnd((int(input.mouseX/currentEndCell.cellSprite.width)),(int(input.mouseY/currentEndCell.cellSprite.height)));
		}
	}

	//set the start marker
	if((input.leftButtonDown == true) && (input.keys[VK_SHIFT] == false))
	{
		if((input.mouseX < boardWidth * defaultCell.cellSprite.width) && (input.mouseY < boardHeight * defaultCell.cellSprite.height)){
			setStart((int(input.mouseX/currentStartCell.cellSprite.width)),(int(input.mouseY/currentStartCell.cellSprite.height)));
		}
	}

	//draw a wall
	if((input.leftButtonDown == true) && (input.keys[VK_SHIFT] == true))
	{
		if((input.mouseX < boardWidth * defaultCell.cellSprite.width) && (input.mouseY < boardHeight * defaultCell.cellSprite.height)){
			drawWall((int(input.mouseX/defaultCell.cellSprite.width)),(int(input.mouseY/defaultCell.cellSprite.height)));
		}
	}
	
	//erase a wall
	if((input.rightButtonDown == true) && (input.keys[VK_SHIFT] == true))
	{
		if((input.mouseX < boardWidth * defaultCell.cellSprite.width) && (input.mouseY < boardHeight * defaultCell.cellSprite.height)){
			eraseWall((int(input.mouseX/defaultCell.cellSprite.width)),(int(input.mouseY/defaultCell.cellSprite.height)));
		}
	}
}

void GameBoard::getBoardImages(LPSTR emptyTilePath,
							  LPSTR wallTilePath,
							  LPSTR startTilePath,
							  LPSTR endTilePath,
							  LPSTR traceBackTilePath,
							  LPSTR oneTilePath,
							  LPSTR twoTilePath,
							  LPSTR threeTilePath,
							  LPSTR fourTilePath,
							  LPSTR fiveTilePath,
							  LPSTR sixTilePath,
							  LPSTR sevenTilePath,
							  LPSTR eightTilePath,
							  LPSTR nineTilePath,
							  LPSTR tenTilePath,
							  LPSTR elevenTilePath,
							  LPSTR twelveTilePath,
							  LPSTR thirteenTilePath,
							  LPSTR fourteenTilePath,
							  LPSTR fifteenTilePath,
							  LPSTR sixteenTilePath,
							  LPSTR seventeenTilePath,
							  LPSTR eighteenTilePath,
							  LPSTR nineteenTilePath,
							  LPSTR twentyTilePath,
							  LPSTR twentyOneTilePath,
							  LPSTR twentyTwoTilePath,
							  LPSTR twentyThreeTilePath,
							  LPSTR twentyFourTilePath,
							  LPSTR twentyFiveTilePath,
							  LPSTR plusTilePath)
{
	emptyTile = LoadABitmap(emptyTilePath);
	wallTile = LoadABitmap(wallTilePath);
	startTile = LoadABitmap(startTilePath);
	endTile = LoadABitmap(endTilePath);
	traceBackTile = LoadABitmap(traceBackTilePath);
	oneTile = LoadABitmap(oneTilePath);
	twoTile = LoadABitmap(twoTilePath);
	threeTile = LoadABitmap(threeTilePath);
	fourTile = LoadABitmap(fourTilePath);
	fiveTile = LoadABitmap(fiveTilePath);
	sixTile = LoadABitmap(sixTilePath);
	sevenTile = LoadABitmap(sevenTilePath);
	eightTile = LoadABitmap(eightTilePath);
	nineTile = LoadABitmap(nineTilePath);
	tenTile = LoadABitmap(tenTilePath);
	elevenTile = LoadABitmap(elevenTilePath);
	twelveTile = LoadABitmap(twelveTilePath);
	thirteenTile = LoadABitmap(thirteenTilePath);
	fourteenTile = LoadABitmap(fourteenTilePath);
	fifteenTile = LoadABitmap(fifteenTilePath);
	sixteenTile = LoadABitmap(sixteenTilePath);
	seventeenTile = LoadABitmap(seventeenTilePath);
	eighteenTile = LoadABitmap(eighteenTilePath);
	nineteenTile = LoadABitmap(nineteenTilePath);
	twentyTile = LoadABitmap(twentyTilePath);
	twentyOneTile = LoadABitmap(twentyOneTilePath);
	twentyTwoTile = LoadABitmap(twentyTwoTilePath);
	twentyThreeTile = LoadABitmap(twentyThreeTilePath);
	twentyFourTile = LoadABitmap(twentyFourTilePath);
	twentyFiveTile = LoadABitmap(twentyFiveTilePath);
	plusTile = LoadABitmap(plusTilePath);
		  /*
		  emptyTile = emptyTilePath
		  wallTile = wallTilePath;
		  startTile = startTilePath;
		  endTile = endTilePath;
		  traceBackTile = traceBackTilePath;
		  oneTile = oneTilePath;
		  twoTile = twoTilePath;
		  threeTile = threeTilePath;
		  fourTile = fourTilePath;
		  fiveTile = fiveTilePath;
		  sixTile = sixTilePath;
		  sevenTile = sevenTilePath;
		  eightTile = eightTilePath;
		  nineTile = nineTilePath;
		  tenTile = tenTilePath;
		  elevenTile = elevenTilePath;
		  twelveTile = twelveTilePath;
		  thirteenTile = thirteenTilePath;
		  fourteenTile = fourteenTilePath;
		  fifteenTile = fifteenTilePath;
		  sixteenTile = sixteenTilePath;
		  seventeenTile = seventeenTilePath;
		  eighteenTile = eighteenTilePath;
		  nineteenTile = nineteenTilePath;
		  twentyTile = twentyTilePath;
		  twentyOneTile = twentyOneTilePath;
		  twentyTwoTile = twentyTwoTilePath;
		  twentyThreeTile = twentyThreeTilePath;
		  twentyFourTile = twentyFourTilePath;
		  twentyFiveTile = twentyFiveTilePath;
		  plusTile = plusTilePath;*/

		  defaultCell.cellSprite.setup(0,0,emptyTilePath);
}

HBITMAP GameBoard::LoadABitmap(LPSTR szFileName)
{
	return (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void GameBoard::setupBoard()
{
	int cellReference = 0;

	for(int i = 0; i < boardWidth; i++)
	{
		for(int j = 0; j < boardHeight; j++)
		{
			boardValues[i][j].cellSprite.setSprite(emptyTile);
			boardValues[i][j].cellSprite.setPosition(i * boardValues[i][j].cellSprite.width, j * boardValues[i][j].cellSprite.height);

			boardValues[i][j].pathFindingValue = 0;
			boardValues[i][j].xGridPos = i;
			boardValues[i][j].yGridPos = j;

			boardValues[i][j].isWall = false;
			boardValues[i][j].isStart = false;
			boardValues[i][j].isEnd = false;
			boardValues[i][j].isTraceBack = false;

			boardValues[i][j].hasChanged = false;

			boardValues[i][j].shouldCheckPathfinding = true;

			boardValues[i][j].cellNumber = cellReference;
			cellReference++;
		}
	}


	setStart(0,0);
	setEnd(boardWidth - 1,boardHeight - 1);

}


// -2 is traceback tile
// -1 is wall tile
// 0 - 15 is 0 - 15 of course
void GameBoard::updateBoard()
{
	for(int i = 0; i < boardWidth; i++)
	{
		for(int j = 0; j < boardHeight; j++)
		{
			if(boardValues[i][j].hasChanged == true)
			{

				if(boardValues[i][j].isWall == true)
				{
					boardValues[i][j].cellSprite.setSprite(wallTile);
				}

				else if(boardValues[i][j].isStart == true)
				{
					boardValues[i][j].cellSprite.setSprite(startTile);
				}

				else if(boardValues[i][j].isEnd == true)
				{
					boardValues[i][j].cellSprite.setSprite(endTile);
				}

				else if(boardValues[i][j].isTraceBack == true)
				{
					boardValues[i][j].cellSprite.setSprite(traceBackTile);
				}

				else
				{
					//Used to have a switch statement here but you cant do less than statement, which was annoying.

					if(boardValues[i][j].pathFindingValue < 0)
					{
						boardValues[i][j].cellSprite.setSprite(emptyTile);
					}
					else if(boardValues[i][j].pathFindingValue == 0)
					{
						boardValues[i][j].cellSprite.setSprite(emptyTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 1)
					{
						boardValues[i][j].cellSprite.setSprite(oneTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 2)
					{
						boardValues[i][j].cellSprite.setSprite(twoTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 3)
					{
						boardValues[i][j].cellSprite.setSprite(threeTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 4)
					{
						boardValues[i][j].cellSprite.setSprite(fourTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 5)
					{
						boardValues[i][j].cellSprite.setSprite(fiveTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 6)
					{
						boardValues[i][j].cellSprite.setSprite(sixTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 7)
					{
						boardValues[i][j].cellSprite.setSprite(sevenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 8)
					{
						boardValues[i][j].cellSprite.setSprite(eightTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 9)
					{
						boardValues[i][j].cellSprite.setSprite(nineTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 10)
					{
						boardValues[i][j].cellSprite.setSprite(tenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 11)
					{
						boardValues[i][j].cellSprite.setSprite(elevenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 12)
					{
						boardValues[i][j].cellSprite.setSprite(twelveTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 13)
					{
						boardValues[i][j].cellSprite.setSprite(thirteenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 14)
					{
						boardValues[i][j].cellSprite.setSprite(fourteenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 15)
					{
						boardValues[i][j].cellSprite.setSprite(fifteenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 16)
					{
						boardValues[i][j].cellSprite.setSprite(sixteenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 17)
					{
						boardValues[i][j].cellSprite.setSprite(seventeenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 18)
					{
						boardValues[i][j].cellSprite.setSprite(eighteenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 19)
					{
						boardValues[i][j].cellSprite.setSprite(nineteenTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 20)
					{
						boardValues[i][j].cellSprite.setSprite(twentyTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 21)
					{
						boardValues[i][j].cellSprite.setSprite(twentyOneTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 22)
					{
						boardValues[i][j].cellSprite.setSprite(twentyTwoTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 23)
					{
						boardValues[i][j].cellSprite.setSprite(twentyThreeTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 24)
					{
						boardValues[i][j].cellSprite.setSprite(twentyFourTile);
					}
					else if(boardValues[i][j].pathFindingValue%tilesNumber == 0)
					{
						boardValues[i][j].cellSprite.setSprite(twentyFiveTile);
					}
					/*
					else if(boardValues[i][j].pathFindingValue > tilesNumber)
					{
						boardValues[i][j].cellSprite.setSprite(plusTile);
					}
					*/
				}
				boardValues[i][j].hasChanged = false;
			}
		}
	}
}

void GameBoard::changePathFindingValue(int newValue, int xPos, int yPos)
{
	boardValues[xPos][yPos].pathFindingValue = newValue;
	boardValues[xPos][yPos].hasChanged = true;

}

void GameBoard::setStart(int xPos, int yPos)
{
	if((boardValues[xPos][yPos].isWall == false) && (boardValues[xPos][yPos].isEnd == false))
	{
		boardValues[currentStartCell.xGridPos][currentStartCell.yGridPos].isStart = false;
		boardValues[currentStartCell.xGridPos][currentStartCell.yGridPos].shouldCheckPathfinding = true;
		boardValues[currentStartCell.xGridPos][currentStartCell.yGridPos].hasChanged = true;
		boardValues[xPos][yPos].isStart = true;
		boardValues[xPos][yPos].hasChanged = true;
		currentStartCell = boardValues[xPos][yPos];

		boardValues[xPos][yPos].isEnd = false;
		boardValues[xPos][yPos].isTraceBack = false;
		boardValues[xPos][yPos].isWall = false;
		boardValues[xPos][yPos].shouldCheckPathfinding = false;
	}
}

void GameBoard::setEnd(int xPos, int yPos)
{
	if((boardValues[xPos][yPos].isStart == false) && (boardValues[xPos][yPos].isWall == false))
	{
		boardValues[currentEndCell.xGridPos][currentEndCell.yGridPos].isEnd = false;
		boardValues[currentEndCell.xGridPos][currentEndCell.yGridPos].hasChanged = true;
		boardValues[xPos][yPos].isEnd = true;
		boardValues[xPos][yPos].hasChanged = true;
		currentEndCell = boardValues[xPos][yPos];

		boardValues[xPos][yPos].isStart = false;
		boardValues[xPos][yPos].isTraceBack = false;
		boardValues[xPos][yPos].isWall = false;
	}
}

void GameBoard::setTraceBack(int xPos, int yPos)
{
	boardValues[xPos][yPos].isTraceBack = true;
	boardValues[xPos][yPos].hasChanged = true;

	boardValues[xPos][yPos].isStart = false;
	boardValues[xPos][yPos].isEnd = false;
	boardValues[xPos][yPos].isWall = false;
}

void GameBoard::drawWall(int xPos, int yPos)
{
	if((boardValues[xPos][yPos].isStart == false) && (boardValues[xPos][yPos].isEnd == false))
	{
		boardValues[xPos][yPos].isWall = true;
		boardValues[xPos][yPos].pathFindingValue = -1;
		boardValues[xPos][yPos].isStart = false;
		boardValues[xPos][yPos].isEnd = false;
		boardValues[xPos][yPos].isTraceBack = false;

		boardValues[xPos][yPos].hasChanged = true;
		boardValues[xPos][yPos].shouldCheckPathfinding = false;
	}
}

void GameBoard::eraseWall(int xPos, int yPos)
{
	if(boardValues[xPos][yPos].isWall == true)
	{
		boardValues[xPos][yPos].isWall = false;
		boardValues[xPos][yPos].hasChanged = true;
		boardValues[xPos][yPos].shouldCheckPathfinding = true;
	}
}

void GameBoard::renderBoard(HDC bitMapHDC,HDC backHDC)
{
	for(int i = 0; i < boardWidth; i++)
	{
		for(int j = 0; j < boardHeight; j++)
		{
			boardValues[i][j].cellSprite.draw(bitMapHDC,backHDC);
		}
	}
}

void GameBoard::reset()
{
	for(int i = 0; i < boardWidth; i++)
	{
		for(int j = 0; j < boardHeight; j++)
		{
			if(boardValues[i][j].isWall == true)
			{
				boardValues[i][j].isWall = false;
				boardValues[i][j].hasChanged = true;
				boardValues[i][j].pathFindingValue = 0;
				boardValues[i][j].shouldCheckPathfinding = true;
			}
			else if(boardValues[i][j].isTraceBack == true)
			{
				boardValues[i][j].isTraceBack = false;
				boardValues[i][j].hasChanged = true;
				boardValues[i][j].pathFindingValue = 0;
				boardValues[i][j].shouldCheckPathfinding = true;
			}
			else if (boardValues[i][j].pathFindingValue != 0)
			{
				changePathFindingValue(0,i,j);
				boardValues[i][j].shouldCheckPathfinding = true;
			}

			setStart(0,0);
			setEnd(boardWidth - 1,boardHeight - 1);
		}
	}
}