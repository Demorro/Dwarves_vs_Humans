#include "Archer.h"


Archer::Archer(void)
{
}


Archer::~Archer(void)
{
}

void Archer::setup(float xGrid, float yGrid, int xTileWidth, int yTileWidth, Race unitRace, LPSTR imagePath)
{
	setupSpecificVariables(xGrid * float(xTileWidth),yGrid * float(yTileWidth), unitRace,"TileSheet.bmp");
}


void Archer::setupSpecificVariables(float xPos, float yPos, Race unitRace, LPSTR imagePath)
{

	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}

	hasMoved = false;
	hasAttacked = false;

	attackType = Unit::Ranged;

	//shunts these 2 static consts down into noraml ints in Unit
	moveValue = moveRange;
	attackValue = attackRange;
	healthValue = health;
	attackDamageValue = attackDamage;

	x = xPos;
	y = yPos;
	findDimensions();

	scaleFactorX = 2;
	scaleFactorY = 2;

	if(unitRace == Dwarf)
	{
		sourceX = 0;
		sourceY = 30;
	}
	else if(unitRace == Human)
	{
		sourceX = 0;
		sourceY = 64;
	}

	width = spriteWidth;
	height = spriteHeight;
	sourceWidth = spriteWidth;
	sourceHeight = spriteHeight;
}
