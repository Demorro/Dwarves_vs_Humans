#include "Unit.h"

Unit::Unit(void)
{
	hasMoved = false;
	hasAttacked = false;
}


Unit::~Unit(void)
{
}

void Unit::resetPieceForTurn()
{
	hasMoved = false;
	hasAttacked = false;
}

void Unit::setup(int xGrid, int yGrid, float inputXTileWidth, float inputYTileWidth, LPSTR imagePath)
{
	hexGridX = xGrid;
	hexGridY = yGrid;
	xTileWidth = inputXTileWidth;
	yTileWidth = inputYTileWidth;
	setupSpecificVariables(float(xGrid * inputXTileWidth),float(yGrid * inputYTileWidth),"TileSheet.bmp");

}

void Unit::moveUnit(int xGrid, int yGrid, HexMap &gameMap)
{
	if((hexGridX >= 0) && (hexGridX < gameMap.mapWidth))
	{
		if((hexGridY >= 0) && (hexGridY < gameMap.mapHeight))
		{
		gameMap.hexMapArray[hexGridX][hexGridY].isOccupied = false;		
		}
	}

	hexGridX = xGrid;
	hexGridY = yGrid;

	gameMap.hexMapArray[hexGridX][hexGridY].isOccupied = true;


	x = (gameMap.hexMapArray[hexGridX][hexGridY].x + xOffset);
	y = (gameMap.hexMapArray[hexGridX][hexGridY].y + yOffset);


	//x = xGrid * xTileWidth;
	//y = yGrid * yTileWidth;
}

void Unit::attack(HexMap &gameMap, int hexTargetX, int hexTargetY, vector<Unit> &enemyUnits)
{
	if(gameMap.hexMapArray[hexTargetX][hexTargetY].isOccupied == true)
	{
		for(int i = 0; i < int(enemyUnits.size()); i++)
		{
			if((enemyUnits[i].hexGridX == hexTargetX) && (enemyUnits[i].hexGridY == hexTargetY))
			{
				enemyUnits[i].healthValue -= attackDamageValue;
			}
		}
	}
}

void Unit::setupSpecificVariables(float xPos, float yPos, LPSTR imagePath)
{

	bitmap = LoadABitmap(imagePath);
	if (!bitmap)
	{
		MessageBox(NULL, "File Not Loaded",imagePath, MB_OK);
	}

	race = Dwarf;
	attackType = Ranged;

	x = xPos;
	y = yPos;
	findDimensions();

	scaleFactorX = 2;
	scaleFactorY = 2;

	sourceX = 0;
	sourceY = 30;

	hasMoved = false;
	hasAttacked = false;

	width = spriteWidth;
	height = spriteHeight;
	sourceWidth = spriteWidth;
	sourceHeight = spriteHeight;
}



void Unit::render(HDC bitmapHDC, HDC backHDC)
{
	drawTrans(bitmapHDC,backHDC);
}

void Unit::drawTrans(HDC bitmapHDC, HDC backHDC)
{	

	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
	TransparentBlt(backHDC, int(x * scaleFactorX), int(y * scaleFactorY), width * scaleFactorX, height * scaleFactorY, bitmapHDC, sourceX, sourceY, sourceWidth, sourceHeight, TRANSPARENT_MASK);
	SelectObject(bitmapHDC,originalBitMap);
}

