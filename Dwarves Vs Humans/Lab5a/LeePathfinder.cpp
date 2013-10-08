#include "LeePathfinder.h"
#include "GameBoard.h"
#include "Cell.h"

LeePathfinder::LeePathfinder(void)
{
}


LeePathfinder::~LeePathfinder(void)
{
}

void LeePathfinder::setup(GameBoard theGameBoard)
{
	gameBoard = theGameBoard;
	voidCell.cellNumber = -1;
	voidCell.isEnd = false;
	voidCell.isStart = false;
	voidCell.isWall = false;
	voidCell.isTraceBack = false;
	voidCell.pathFindingValue = -99;
	voidCell.xGridPos = -1;
	voidCell.yGridPos = -1;
	waveExpandActive = true;
	shouldExecute = false;
}

void LeePathfinder::execute()
{
	getStartAndEndPoints();
	workingCells.push(startPoint);
	if(waveExpandActive == true)
	{
		waveExpansion();
	}
	else if(backTraceActive == true)
	{
		backTrace();
	}
	if((waveExpandActive == false) && (backTraceActive == false))
	{
		shouldExecute =false;
	}

}


int LeePathfinder::waveExpansion()
{

	Cell currentCell;
	if(workingCells.size() > 0)
	{
		currentCell = workingCells.front();
	}
	else
	{
		return 0;
	}
	
	//check if we are at the end
	if((gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos - 1].isEnd == true) && (gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].yGridPos  > 0))
	{
		waveExpandActive = false;
		backTraceActive = true;
		endPoint.pathFindingValue = gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].pathFindingValue + 1;
		setPathFindingToggle();
		clearQueue(workingCells);
		workingTraceBackCell = endPoint;
	}
	else if((gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos + 1].isEnd == true) && (gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].yGridPos < gameBoard.boardHeight - 1))
	{
		waveExpandActive = false;
		backTraceActive = true;
		endPoint.pathFindingValue = gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].pathFindingValue + 1;
		setPathFindingToggle();
		clearQueue(workingCells);
		workingTraceBackCell = endPoint;
	}
	else if((gameBoard.boardValues[currentCell.xGridPos - 1][currentCell.yGridPos].isEnd == true) && (gameBoard.boardValues[currentCell.xGridPos ][currentCell.yGridPos - 1].xGridPos  > 0))
	{
		waveExpandActive = false;
		backTraceActive = true;
		endPoint.pathFindingValue = gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].pathFindingValue + 1;
		setPathFindingToggle();
		clearQueue(workingCells);
		workingTraceBackCell = endPoint;
	}
	else if((gameBoard.boardValues[currentCell.xGridPos + 1][currentCell.yGridPos].isEnd == true) && (gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].xGridPos  < gameBoard.boardWidth - 1))
	{
		waveExpandActive = false;
		backTraceActive = true;
		endPoint.pathFindingValue = gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].pathFindingValue + 1;
		setPathFindingToggle();
		clearQueue(workingCells);
		workingTraceBackCell = endPoint;
	}
	

	//North
	if(waveExpandActive == true)
	{
		
		if(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].yGridPos  > 0)
		{
			if(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos - 1].shouldCheckPathfinding == true) //If the north cell is valid for pathfinding
			{
				//increment the pathfindingvalue on the candidate cell to one plus this one
				gameBoard.changePathFindingValue(currentCell.pathFindingValue + 1, currentCell.xGridPos, currentCell.yGridPos - 1);

				//add the candidate cell to the bottom of the working set
				workingCells.push(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos - 1]);

				//change that cells pathfinding toggle
				gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos - 1].shouldCheckPathfinding = false;
			}
		}
	
	
		//East
	
		if(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].xGridPos  < gameBoard.boardWidth - 1)
		{
			if(gameBoard.boardValues[currentCell.xGridPos + 1][currentCell.yGridPos].shouldCheckPathfinding == true) //If the east cell is valid for pathfinding
			{
				//increment the pathfindingvalue on the candidate cell to one plus this one
				gameBoard.changePathFindingValue(currentCell.pathFindingValue + 1, currentCell.xGridPos + 1, currentCell.yGridPos);

				//add the candidate cell to the bottom of the working set
				workingCells.push(gameBoard.boardValues[currentCell.xGridPos + 1][currentCell.yGridPos]);

				//change that cells pathfinding toggle
				gameBoard.boardValues[currentCell.xGridPos + 1][currentCell.yGridPos].shouldCheckPathfinding = false;
			}
		}
	
		//South
		if(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].yGridPos < gameBoard.boardHeight - 1)
		{
			if(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos + 1].shouldCheckPathfinding == true) //If the south cell is valid for pathfinding
			{
				//increment the pathfindingvalue on the candidate cell to one plus this one
				gameBoard.changePathFindingValue(currentCell.pathFindingValue + 1, currentCell.xGridPos, currentCell.yGridPos + 1);

				//add the candidate cell to the bottom of the working set
				workingCells.push(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos + 1]);

				//change that cells pathfinding toggle
				gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos + 1].shouldCheckPathfinding = false;
			}
		}
		
	
		//West
		if(gameBoard.boardValues[currentCell.xGridPos][currentCell.yGridPos].xGridPos  > 0)
		{
			if(gameBoard.boardValues[currentCell.xGridPos - 1][currentCell.yGridPos].shouldCheckPathfinding == true) //If the west cell is valid for pathfinding
			{
				//increment the pathfindingvalue on the candidate cell to one plus this one
				gameBoard.changePathFindingValue(currentCell.pathFindingValue + 1, currentCell.xGridPos - 1, currentCell.yGridPos);

				//add the candidate cell to the bottom of the working set
				workingCells.push(gameBoard.boardValues[currentCell.xGridPos - 1][currentCell.yGridPos]);

				//change that cells pathfinding toggle
				gameBoard.boardValues[currentCell.xGridPos - 1][currentCell.yGridPos].shouldCheckPathfinding = false;
			}
		}
	
	
		//pop the currentCell off the top of the working set after checking north south east and west
		if(workingCells.size() > 0)
		{
			workingCells.pop();
		}

	}
	return 0;
}		


void LeePathfinder::backTrace()
{
	Cell candidateCell;
	for(int i = 0; i < 4; i++) //For north, south, east and west, 0, 1, 2 and 3
	{
		if(i == 0) //North
		{
			candidateCell = gameBoard.boardValues[workingTraceBackCell.xGridPos][workingTraceBackCell.yGridPos - 1];
			stopBoardOverFlows(candidateCell);
			if(candidateCell.yGridPos  >= 0) //Check if the north cell is on the board
			{
				if(candidateCell.shouldCheckPathfinding == true)
				{
					//Check if we are back at the start
					if(candidateCell.isStart == true)
					{
						backTraceActive = false;
						break;
					}

					if(candidateCell.pathFindingValue == workingTraceBackCell.pathFindingValue - 1)
					{
						gameBoard.setTraceBack(candidateCell.xGridPos,candidateCell.yGridPos);
						candidateCell.shouldCheckPathfinding = false;
						workingTraceBackCell = candidateCell;
					}
				}
			}
		}
		else if (i == 1) //East
		{
			candidateCell = gameBoard.boardValues[workingTraceBackCell.xGridPos + 1][workingTraceBackCell.yGridPos];
			stopBoardOverFlows(candidateCell);
			if(candidateCell.xGridPos < gameBoard.boardWidth) //Check if the north cell is on the board
			{
				if(candidateCell.shouldCheckPathfinding == true)
				{
					//Check if we are back at the start
					if(candidateCell.isStart == true)
					{
						backTraceActive = false;
						break;
					}

					if(candidateCell.pathFindingValue == workingTraceBackCell.pathFindingValue - 1)
					{
						gameBoard.setTraceBack(candidateCell.xGridPos,candidateCell.yGridPos);
						candidateCell.shouldCheckPathfinding = false;
						workingTraceBackCell = candidateCell;
					}
				}
			}
		}
		else if (i == 2) //South
		{
			candidateCell = gameBoard.boardValues[workingTraceBackCell.xGridPos][workingTraceBackCell.yGridPos + 1];
			stopBoardOverFlows(candidateCell);
			if(candidateCell.yGridPos  < gameBoard.boardHeight) //Check if the south cell is on the board
			{
				if(candidateCell.shouldCheckPathfinding == true)
				{
					//Check if we are back at the start
					if(candidateCell.isStart == true)
					{
						backTraceActive = false;
						break;
					}

					if(candidateCell.pathFindingValue == workingTraceBackCell.pathFindingValue - 1)
					{
						gameBoard.setTraceBack(candidateCell.xGridPos,candidateCell.yGridPos);
						candidateCell.shouldCheckPathfinding = false;
						workingTraceBackCell = candidateCell;
					}
				}
			}
		}
		else if (i == 3) //West
		{
			candidateCell = gameBoard.boardValues[workingTraceBackCell.xGridPos - 1][workingTraceBackCell.yGridPos];
			stopBoardOverFlows(candidateCell);
			if(candidateCell.xGridPos  >= 0) //Check if the west cell is on the board
			{
				if(candidateCell.shouldCheckPathfinding == true)
				{
					//Check if we are back at the start
					if(candidateCell.isStart == true)
					{
						backTraceActive = false;
						break;
					}
					
					if(candidateCell.pathFindingValue == workingTraceBackCell.pathFindingValue - 1)
					{

						gameBoard.setTraceBack(candidateCell.xGridPos,candidateCell.yGridPos);
						candidateCell.shouldCheckPathfinding = false;
						workingTraceBackCell = candidateCell;
					}
				}
			}
		}
	}
}

//Wrote this function late at night after having an epiphany while lying in bed. It would go west at the start when the start was in top left and the bottom in top right not because of some arcane bug in the for loop
//but rather because when it was checking the down cell, it was in fact overflowing off the board and actually checking the very top left, which happened to be the start cell. So the program though it was finished and didnt bother doing anything.
void LeePathfinder::stopBoardOverFlows(Cell &candidateCell)
{
	if((candidateCell.xGridPos > workingTraceBackCell.xGridPos + 1) || (candidateCell.xGridPos < workingTraceBackCell.xGridPos - 1))
	{
		candidateCell.shouldCheckPathfinding = false;
	}
	if((candidateCell.yGridPos > workingTraceBackCell.yGridPos + 1) || (candidateCell.yGridPos < workingTraceBackCell.yGridPos - 1))
	{
		candidateCell.shouldCheckPathfinding = false;
	}
}

void LeePathfinder::update(GameBoard theGameBoard)
{
	gameBoard = theGameBoard;
}

void LeePathfinder::reset(GameBoard theGameBoard)
{
	clearQueue(workingCells);
	setup(theGameBoard);
}
void LeePathfinder::getStartAndEndPoints()
{
	//Set start and end points from passed in gameBoard
	for(int i = 0; i < gameBoard.boardWidth; i++)
	{
		for(int j = 0; j < gameBoard.boardHeight; j++)
		{
			if(gameBoard.boardValues[i][j].isStart == true)
			{
				startPoint = gameBoard.boardValues[i][j];
			}

			if(gameBoard.boardValues[i][j].isEnd == true)
			{
				endPoint = gameBoard.boardValues[i][j];
			}
		}
	}
}

void LeePathfinder::setPathFindingToggle()
{
	for(int i = 0; i <= gameBoard.boardWidth; i++)
	{
		for(int j = 0; j <= gameBoard.boardHeight; j++)
		{
			if(gameBoard.boardValues[i][j].isWall == false)
			{
				if(gameBoard.boardValues[i][j].isTraceBack == false)
				{
					gameBoard.boardValues[i][j].shouldCheckPathfinding = true;
				}
			}
		}
	}
}

void LeePathfinder::clearQueue(queue<Cell> &q )
{
   std::queue<Cell> empty;
   std::swap( q, empty );
}


/* This might be useful later if i want an option to display contents of duplicates list
void LeePathfinder::checkDuplicatesList(LPSTR checkSpritePath)
{
	Cell transitionCell;
	for(int i = 0; i < duplicateCells.size(); i++)
	{
		gameBoard.boardValues[duplicateCells.front().xGridPos][duplicateCells.front().yGridPos].isWall = false;
		gameBoard.boardValues[duplicateCells.front().xGridPos][duplicateCells.front().yGridPos].isTraceBack = true;
		gameBoard.boardValues[duplicateCells.front().xGridPos][duplicateCells.front().yGridPos].hasChanged = true;

		transitionCell = duplicateCells.front();
		duplicateCells.pop_front();
		duplicateCells.push_back(transitionCell);
	}
}
*/