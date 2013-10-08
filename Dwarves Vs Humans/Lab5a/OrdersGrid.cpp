#include "OrdersGrid.h"
#include <queue>

using namespace std;


OrdersGrid::OrdersGrid(void)
{
}


OrdersGrid::~OrdersGrid(void)
{
}


void OrdersGrid::flood(int xOffset, int yOffset, HexTile &currentTile, int gridRange, HexMap &gameMap, queue<HexTile> &workingQueue, int &workingStepCost,HexTile::terrainType terrain,Unit::AttackType attackType)
{

	if(terrain == HexTile::moveSelection)
	{
		if((currentTile.hexGridX + xOffset >= 0) && (currentTile.hexGridX + xOffset < gameMap.mapWidth)) //if we're on the grid horizontally
		{
			if((currentTile.hexGridY + yOffset >= 0) && (currentTile.hexGridY + yOffset < gameMap.mapHeight)) //if we're on the grid verticaly
			{
				if(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].checkPathfinding == true)
				{
					if((gameMap.hexMapArray[currentTile.hexGridX][currentTile.hexGridY].pathFindingValue + gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].moveCost) <= gridRange) //if we can move to the next tile
					{
						//candidate pathfindingvalue = currentcells pathfindingvalue + candidates movecode
						gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].pathFindingValue = (gameMap.hexMapArray[currentTile.hexGridX][currentTile.hexGridY].pathFindingValue + gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].moveCost);
						gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].setTerrain(HexTile::moveSelection);
						gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].checkPathfinding = false;
						gridVector.push_back(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset]);
						workingQueue.push(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset]);
						//check we are taking the shortest route
						//if weve checked pathfinding on this tile

					}
				}
			}
		}
	}
	else if(terrain == HexTile::attackSelection)
	{
		if((currentTile.hexGridX + xOffset >= 0) && (currentTile.hexGridX + xOffset < gameMap.mapWidth)) //if we're on the grid horizontally
		{
			if((currentTile.hexGridY + yOffset >= 0) && (currentTile.hexGridY + yOffset < gameMap.mapHeight)) //if we're on the grid verticaly
			{
				if(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].checkPathfinding == true)
				{
					if(attackType == Unit::Ranged)
					{
						if((gameMap.hexMapArray[currentTile.hexGridX][currentTile.hexGridY].pathFindingValue + gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].rangedAttackCost) <= gridRange) //if we can move to the next tile
						{
							//candidate pathfindingvalue = currentcells pathfindingvalue + candidates movecode
							gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].pathFindingValue = (gameMap.hexMapArray[currentTile.hexGridX][currentTile.hexGridY].pathFindingValue + gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].rangedAttackCost);
							gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].setTerrain(HexTile::attackSelection);
							gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].checkPathfinding = false;
							gridVector.push_back(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset]);
							workingQueue.push(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset]);
							//check we are taking the shortest route
							//if weve checked pathfinding on this tile

						}
					}
					else if(attackType == Unit::Melee)
					{
						if((gameMap.hexMapArray[currentTile.hexGridX][currentTile.hexGridY].pathFindingValue + gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].meleeAttackCost) <= gridRange) //if we can move to the next tile
						{
							//candidate pathfindingvalue = currentcells pathfindingvalue + candidates movecode
							gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].pathFindingValue = (gameMap.hexMapArray[currentTile.hexGridX][currentTile.hexGridY].pathFindingValue + gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].meleeAttackCost);
							gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].setTerrain(HexTile::attackSelection);
							gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset].checkPathfinding = false;
							gridVector.push_back(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset]);
							workingQueue.push(gameMap.hexMapArray[currentTile.hexGridX + xOffset][currentTile.hexGridY + yOffset]);
							//check we are taking the shortest route
							//if weve checked pathfinding on this tile

						}
					}
				}
			}
		}
	}
}

void OrdersGrid::generateMoveGrid(int hexGridStartX, int hexGridStartY, int range, HexMap &gameMap)
{
	//every step takes 2, because then road can only take one, and forest can take 4
	int gridRange = range * 2;
	int workingStepCost = 0;

	HexTile currentTile;
	queue<HexTile> workingQueue;

	gameMap.hexMapArray[hexGridStartX][hexGridStartY].setTerrain(HexTile::moveSelection);
	gridVector.push_back(gameMap.hexMapArray[hexGridStartX][hexGridStartY]);
	workingQueue.push(gameMap.hexMapArray[hexGridStartX][hexGridStartY]);

	//flood out

	while(workingQueue.size() > 0)
	{
		currentTile = workingQueue.front();
		//checkForShortestPath(gameMap,currentTile);
		if(currentTile.hexGridY % 2 != 0) //if we are on a pushed along row(odd)
		{
			//up
			flood(0,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//top right
			flood(1,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//right
			flood(1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//bottom right
			flood(1,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//down
			flood(0,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//left
			flood(-1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
		}
		else if(currentTile.hexGridY % 2 == 0) //if we are on a non-pushed along row(even)
		{
			//up
			flood(0,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//right
			flood(1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//down
			flood(0,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//bottom left
			flood(-1,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//left
			flood(-1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
			//top left
			flood(-1,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::moveSelection,Unit::Ranged);
		}
		workingQueue.pop();
	}
}


void OrdersGrid::generateAttackGrid(int hexGridStartX, int hexGridStartY, int range, HexMap &gameMap, Unit::AttackType attackType)
{
	//every step takes 2, because then road can only take one, and forest can take 4
	int gridRange = range * 2;
	int workingStepCost = 0;

	HexTile currentTile;
	queue<HexTile> workingQueue;

	gameMap.hexMapArray[hexGridStartX][hexGridStartY].setTerrain(HexTile::attackSelection);
	gridVector.push_back(gameMap.hexMapArray[hexGridStartX][hexGridStartY]);
	workingQueue.push(gameMap.hexMapArray[hexGridStartX][hexGridStartY]);

	//flood out

	while(workingQueue.size() > 0)
	{
		currentTile = workingQueue.front();
		//checkForShortestPath(gameMap,currentTile);
		if(currentTile.hexGridY % 2 != 0) //if we are on a pushed along row(odd)
		{
			//up
			flood(0,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//top right
			flood(1,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//right
			flood(1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//bottom right
			flood(1,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//down
			flood(0,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//left
			flood(-1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
		}
		else if(currentTile.hexGridY % 2 == 0) //if we are on a non-pushed along row(even)
		{
			//up
			flood(0,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//right
			flood(1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//down
			flood(0,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//bottom left
			flood(-1,1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//left
			flood(-1,0,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
			//top left
			flood(-1,-1,currentTile,gridRange,gameMap,workingQueue,workingStepCost,HexTile::attackSelection,attackType);
		}
		workingQueue.pop();
	}
}

void OrdersGrid::eraseGrid(HexMap &gameMap)
{
	for(int i = 0; i < int(gridVector.size()); i++)
	{
		gameMap.hexMapArray[gridVector[i].hexGridX][gridVector[i].hexGridY].setTerrain(gameMap.hexMapArray[gridVector[i].hexGridX][gridVector[i].hexGridY].startTerrain);
		gameMap.hexMapArray[gridVector[i].hexGridX][gridVector[i].hexGridY].pathFindingValue = 0;
		gameMap.hexMapArray[gridVector[i].hexGridX][gridVector[i].hexGridY].checkPathfinding = true;
	}
}
