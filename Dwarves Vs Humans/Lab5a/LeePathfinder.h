#pragma once
#include <deque>
#include <queue>
#include "GameBoard.h"
#include "Cell.h"

using namespace std;

class LeePathfinder
{
public:
	LeePathfinder(void);
	~LeePathfinder(void);

	Cell startPoint;
	Cell endPoint;
	Cell workingTraceBackCell;

	queue<Cell> workingCells; //this is the working set

	GameBoard gameBoard;
	bool backTraceActive;
	bool shouldExecute;

	void setup(GameBoard theGameBoard);
	void execute();
	int waveExpansion();
	void backTrace();
	void update(GameBoard theGameBoard);
	//void checkDuplicatesList(LPSTR checkSpritePath);
	void addWallsToDuplicateList();
	bool searchQueue(queue<Cell> searchQueue, Cell searchItem);
	void reset(GameBoard theGameBoard);
	void setPathFindingToggle();

private:
	Cell voidCell;
	void getStartAndEndPoints();
	bool waveExpandActive;
	void clearQueue(queue<Cell> &q);
	void stopBoardOverFlows(Cell &candidateCell);
};

