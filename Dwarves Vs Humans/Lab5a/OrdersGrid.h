#pragma once

#include <vector>
#include "HexMap.h"
#include "HexTile.h"
#include "TransGraphic.h"
#include "Unit.h"


class OrdersGrid
{
public:
	OrdersGrid(void);
	~OrdersGrid(void);

	vector<HexTile> gridVector;

	void generateMoveGrid(int hexGridStartX, int hexGridStartY, int range, HexMap &gameMap);
	void generateAttackGrid(int hexGridStartX, int hexGridStartY, int range, HexMap &gameMap,Unit::AttackType);

	//These two functions are used in generateGrid
	void flood(int xOffset, int yOffset, HexTile &currentTile, int gridRange, HexMap &gameMap, queue<HexTile> &workingQueue, int &workingStepCost,HexTile::terrainType terrain,Unit::AttackType);
	void eraseGrid(HexMap &gameMap);
};

