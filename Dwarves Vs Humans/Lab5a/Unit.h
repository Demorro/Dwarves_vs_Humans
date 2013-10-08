#pragma once

#include "HexMap.h"
#include "HexHighlight.h"
#include "WindowsInput.h"
#include "WindowsSprite.h"
#include <vector>
#include "TransGraphic.h"


using namespace std;

class Unit :
	public WindowsSprite
{
public:
	static const int spriteWidth = 14;
	static const int spriteHeight = 16;

	//The offsets when standing on a tile
	static const int xOffset = 3;
	static const int yOffset = -1;

	//the moveRangeValue of the unit
	int moveValue;
	//the attackRangeValue of the unit
	int attackValue;
	//the health value of the unit
	int healthValue;
	//the damage value of the unit
	int attackDamageValue;

	bool hasMoved;
	bool hasAttacked;

	Unit(void);
	~Unit(void);

	enum Race
	{
		Dwarf,
		Human,
	};

	enum AttackType
	{
		Ranged,
		Melee,
	};

	Race race;
	AttackType attackType;

	void resetPieceForTurn();
	void drawTrans(HDC bitmapHDC, HDC backHDC);
	void render(HDC bitmapHDC, HDC backHDC);

	//Scales x and y for the tiles, probably wont be changed through the code
	int scaleFactorX;
	int scaleFactorY;

	//Adjusting these should change the rect used on the spriteSheet
	int sourceX;
	int sourceY;

	int sourceWidth;
	int sourceHeight;

	//gridPositions
	int hexGridX;
	int hexGridY;

	void moveUnit(int xGrid, int yGrid, HexMap &gameMap);
	void attack(HexMap &gameMap, int hexTargetX, int hexTargetY, vector<Unit> &enemyUnits);

protected:
	void setup(int xGrid, int yGrid, float inputXTileWidth, float intputYTileWidth, LPSTR imagePath);
	void setupSpecificVariables(float xPos, float yPos, LPSTR imagePath);

	int xTileWidth;
	int yTileWidth;

private:
};

